#ifndef BlockOf
#define BlockOf_H

#include <cstddef>
#include <initializer_list>

#define PLACEMENT_NEW_CONSTRUCTION

template<typename T>
class BlockOf {
    std::size_t sz;
#ifndef PLACEMENT_NEW_CONSTRUCTION
    T *data;
#else
    char *data;
#endif
public:
    BlockOf(const BlockOf&) = delete;
    BlockOf& operator=(const BlockOf&) = delete;
    BlockOf(BlockOf&& init)
        : sz(init.sz), data(init.data) {
        init.sz = 0;
        init.data = nullptr;
    }
#ifndef PLACEMENT_NEW_CONSTRUCTION
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
#else
    BlockOf& operator=(BlockOf&& rhs) {
        if (data != rhs.data) {
            this->~BlockOf<T>();
            sz = rhs.sz; rhs.sz = 0;
            data = rhs.data; rhs.data = nullptr;
        }
        return *this;
    }
    BlockOf(std::size_t sz_)
        : sz(sz_), data(new char[sz_*sizeof(T)]) {
        for (std::size_t i = 0; i < sz_; ++i)
            new(data + i*sizeof(T)) T();
    }
    BlockOf(const std::initializer_list<T> &ilist) 
        : sz(0) // !! copy-loop following depends on this
        , data(new char[ilist.size()*sizeof(T)]) {
        for (const auto &v : ilist)
            new(data + (sz++)*sizeof(T)) T(v);
    }
    ~BlockOf() {
        while (sz > 0)
            reinterpret_cast<T*>(data + (--sz)*sizeof(T))->~T();
        delete[] data;
    }
#endif
    T& operator[](std::size_t idx) {
        return reinterpret_cast<T*>(data)[idx];
    }
    const T& operator[](std::size_t idx) const {
        return reinterpret_cast<const T*>(data)[idx];
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
};

#endif
