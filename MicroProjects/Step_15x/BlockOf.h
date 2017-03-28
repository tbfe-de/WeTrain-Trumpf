#ifndef BlockOf
#define BlockOf_H

#include <cstddef>
#include <exception>
#include <stdexcept>
#include <functional>
#include <initializer_list>

#include <boost/exception/exception.hpp>
#include <boost/exception/error_info.hpp>
#include <boost/exception/info.hpp>

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
        : /*virtual std::exception
        ,*/ virtual boost::exception {};
    struct tag_bad_index {};
    struct tag_max_index {};
    typedef boost::error_info<struct tag_bad_index, std::size_t> bad_index;
    typedef boost::error_info<struct tag_max_index, std::size_t> max_index;

private:
    std::size_t check_throw(std::size_t idx) {
        OutOfRange e;
        if (idx >= sz) {
            e << bad_index(idx);
            if (sz > 0)
                e << max_index(idx);
            throw std::move(e);
        }
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
};

#endif
