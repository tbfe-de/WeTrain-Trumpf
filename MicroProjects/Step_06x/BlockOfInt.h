#ifndef BlockOfInt
#define BlockOfInt_H

#include <cstddef>
#include <initializer_list>

#include <boost/utility/value_init.hpp>

class BlockOfInt {
    std::size_t sz;
    boost::value_initialized<int> *data;
public:
    BlockOfInt(const BlockOfInt&) = delete;
    BlockOfInt& operator=(const BlockOfInt&) = delete;
    BlockOfInt(BlockOfInt&& init)
        : sz(init.sz), data(init.data) {
        init.sz = 0;
        init.data = nullptr;
    }
    BlockOfInt& operator=(BlockOfInt&& rhs) {
        if (data != rhs.data) {
            delete[] data;
            sz = rhs.sz; rhs.sz = 0;
            data = rhs.data; rhs.data = nullptr;
        }
        return *this;
    }
    BlockOfInt(std::size_t sz_)
        : sz(sz_), data(new boost::value_initialized<int>[sz_])
    {}
    BlockOfInt(const std::initializer_list<int> &ilist) 
        : sz(0) // !! copy-loop following depends on this
        , data(new boost::value_initialized<int>[ilist.size()])
    {
          for (int v : ilist)
              boost::get(data[sz++]) = v;
    }
    ~BlockOfInt() {
        delete[] data;
    }
    int& operator[](std::size_t idx) {
        return boost::get(data[idx]);
    }
    const int& operator[](std::size_t idx) const {
        return boost::get(data[idx]);
    }
    std::size_t size() const {
        return sz;
    }
    void swap(BlockOfInt& other) {
        const auto tmp_sz = sz;
        const auto tmp_data = data;
        sz = other.sz;
        data = other.data;
        other.sz = tmp_sz;
        other.data = tmp_data;
    }
};

#endif
