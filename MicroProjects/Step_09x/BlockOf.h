#ifndef BlockOf
#define BlockOf_H

#include <cstddef>
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
    typedef T* iterator;
#if 0
    iterator begin() { return data; }
    iterator end() { return data+sz; }
#ifdef NEEDS_CONST_ITERATOR_TOO
    typedef T* const_iterator;
    const_iterator begin() const { return data; }
    const_iterator end() const { return data+sz; }
    const_iterator cbegin() const { return data; }
    const_iterator cend() const { return data+sz; }
#endif
#endif
};

#if 1
namespace std {
    template<typename T>
    T* begin(BlockOf<T> &block) { return &block[0]; }
    template<typename T>
    T* end(BlockOf<T> &block) { return &block[block.size()]; }
#ifdef NEEDS_CONST_ITERATOR_TOO
    template<typename T>
    const T* begin(const BlockOf<T> &block) { return &block[0]; }
    template<typename T>
    const T* end(const BlockOf<T> &block) { return &block[block.size()]; }
#endif
}
#endif

#endif
