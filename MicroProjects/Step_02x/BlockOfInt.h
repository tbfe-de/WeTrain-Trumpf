#ifndef BlockOfInt
#define BlockOfInt_H

#include <cstddef>

class BlockOfInt {
    std::size_t sz;
    int* data;
public:
    BlockOfInt(std::size_t sz_)
        : sz(sz_), data(new int[sz_])
    {}
    ~BlockOfInt() {
        delete[] data;
    }
    int& operator[](std::size_t idx) {
        return data[idx];
    }
    const int& operator[](std::size_t idx) const {
        return data[idx];
    }
    std::size_t size() const {
        return sz;
    }
};

#endif
