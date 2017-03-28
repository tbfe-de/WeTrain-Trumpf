#ifndef BlockOf
#define BlockOf_H

#include <cstddef>
#include <stdexcept>
#include <functional>
#include <initializer_list>

template<typename T>
class BlockOf {
    std::size_t sz;
    T* data;
public:
#define MAKING_COPY_IS_IMPLEMENTED
#ifdef  MAKING_COPY_IS_IMPLEMENTED
    BlockOf(const BlockOf& init)
        : sz(init.sz), data(new T[init.sz])
    {
        for (std::size_t i = 0; i < sz; ++i)
            data[i] = init.data[i];
    }
    BlockOf& operator=(const BlockOf& rhs) {
        if (data != rhs.data) {
            delete[] data;
            sz = rhs.sz;
            data = new T[sz];
            for (std::size_t i = 0; i < sz; ++i)
                data[i] = rhs.data[i];
        }
        return *this;
    }
#else
    BlockOf(const BlockOf&) = delete;
    BlockOf& operator=(const BlockOf&) = delete;
#endif

    BlockOf(BlockOf&& init)
        : sz(init.sz), data(init.data) {
        init.sz = 0;
        init.data = nullptr;
    }
    BlockOf& operator=(BlockOf&& rhs) {
        if (data != rhs.data) {
            delete[] data;
            sz = rhs.sz; rhs.sz = 0;
            data = rhs.data; rhs.data = nullptr;
        }
        return *this;
    }
    BlockOf(std::size_t sz_)
        : sz(sz_), data(new T[sz_])
    {
        for (auto i = 0; i < sz; ++i)
            data[i] = T();
    }
    BlockOf(const std::initializer_list<T> &ilist) 
        : sz(0), data(new T[ilist.size()])
    {
        for (auto v : ilist)
            data[sz++] = v;
    }
    ~BlockOf() {
        delete[] data;
    }
    struct OutOfRange
        : public std::out_of_range {
        const std::size_t idx;
        const std::size_t max;
        OutOfRange(std::size_t idx_, std::size_t max_)
            : std::out_of_range("bad index for BlockOf<T>")
            , idx(idx_), max(max_)
        {}
    };
private:
    std::size_t check_throw(std::size_t idx) {
        if (idx >= sz)
            throw OutOfRange(idx, sz-1);
        return idx;
    }
public:
    T& at(std::size_t idx) {
        return data[check_throw(idx)];
    }
    const T& at(std::size_t idx) const {
        return data[check_throw(idx)];
    }
    T& operator[](std::size_t idx) {
        return data[idx];
    }
    const T& operator[](std::size_t idx) const {
        return data[idx];
    }
    std::size_t size() const {
        return sz;
    }
    void swap(BlockOf& other) {
        const auto tmp_sz = sz;
        const auto tmp_data = data;
        sz = other.sz;
        data = other.data;
        other.sz = tmp_sz;
        other.data = tmp_data;
    }
    class iterator;
    class const_iterator;
    const_iterator cbegin() const;
    const_iterator cend() const;
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
};

template<class T>
class BlockOf<T>::const_iterator {
    friend BlockOf<T>::const_iterator BlockOf<T>::cbegin() const;
    friend BlockOf<T>::const_iterator BlockOf<T>::cend() const;
    friend BlockOf<T>::const_iterator BlockOf<T>::begin() const;
    friend BlockOf<T>::const_iterator BlockOf<T>::end() const;
    friend bool operator==(const BlockOf<T>::const_iterator lhs,
                           const BlockOf<T>::const_iterator rhs) {
        return (lhs.elem_ptr == rhs.elem_ptr);
    }

    const T* elem_ptr;
protected:
    const_iterator(const T* init)
        : elem_ptr(init)
    {}
public:
    const_iterator()
        : elem_ptr(nullptr)
    {}
    const T& operator*() const {
        return *elem_ptr;
    }
    BlockOf<T>::const_iterator& operator++() {
        ++elem_ptr;
        return *this;
    }
    BlockOf<T>::const_iterator operator++(int) {
        return BlockOf<T>::const_iterator(elem_ptr++);
    }
};

template<class T>
auto BlockOf<T>::cbegin() const -> const_iterator {
    return data;
}

template<class T>
auto BlockOf<T>::begin() const -> const_iterator {
    return cbegin();
}

template<class T>
auto BlockOf<T>::cend() const -> const_iterator {
    return data + sz;
}

template<class T>
auto BlockOf<T>::end() const -> const_iterator {
    return cend();
}

template<class T>
class BlockOf<T>::iterator
    : public BlockOf<T>::const_iterator {
    friend BlockOf<T>::iterator BlockOf<T>::begin();
    friend BlockOf<T>::iterator BlockOf<T>::end();
    iterator(T* init)
        : const_iterator(init)
    {}
public:
    iterator()
        : const_iterator()
    {}
    T& operator*() {
        return const_cast<T&>(const_iterator::operator*());
    }
    iterator& operator++() {
        const_iterator::operator++();
        return *this;
    }
    iterator operator++(int) {
        auto result(*this);
        const_iterator::operator++();
        return result;
    }
};

template<class T>
auto BlockOf<T>::begin() -> iterator {
    return data;
}

template<class T>
auto BlockOf<T>::end() -> iterator {
    return data + sz;
}

#endif
