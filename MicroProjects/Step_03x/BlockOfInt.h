#ifndef BlockOfInt
#define BlockOfInt_H

#include <cstddef>

class BlockOfInt {
public:
    typedef std::size_t size_type;
//  using size_type = std::size_t;
private:
    size_type sz;
    int* data;
public:
    BlockOfInt(size_type sz_)
        : sz(sz_), data(new int[sz_])
    {}
    BlockOfInt(const BlockOfInt& init)
       : sz(init.sz), data(new int[init.sz]) {
       for (size_type i = 0; i < sz; ++i)
           data[i] = init.data[i];
    }
    ~BlockOfInt() {
        delete[] data;
    }
    BlockOfInt& operator=(const BlockOfInt& rhs) {
       if (data != rhs.data) {
           delete[] data;
           sz = rhs.sz;
           data = new int[sz];
           for (size_type i = 0; i < sz; ++i)
               data[i] = rhs.data[i];
       }
       return *this;
    }
    int& operator[](size_type idx) {
        return data[idx];
    }
    const int& operator[](size_type idx) const {
        return data[idx];
    }
    size_type size() const {
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
