#ifndef BlockOfInt
#define BlockOfInt_H

#include <cstddef>

class BlockOfInt {
    std::size_t sz; // (1) !! ORDER DEPENDENCY
    int* data;      // (2) !! ORDER DEPENDENCY
public:
    BlockOfInt(std::size_t sz_)
        : sz(sz_), data(new int[sz])
// or   : sz(sz_), data(new int[sz_]) // without order dependency
    {}
    ~BlockOfInt() {
        delete[] data;
    }
    int& operator[](std::size_t idx) {
        return data[idx];
    }
    std::size_t size() const {
        return sz;
    }
};

#endif
