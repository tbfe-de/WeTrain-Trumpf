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
    void swap(BlockOfInt& other) {
//   ?? assert(size == other.size); ??
        const auto tmp_sz = sz;
        const auto tmp_data = data;
        sz = other.sz;
        data = other.data;
        other.sz = tmp_sz;
        other.data = tmp_data;
    }
};

#endif
