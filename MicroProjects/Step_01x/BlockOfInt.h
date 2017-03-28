#ifndef BlockOfInt
#define BlockOfInt_H

#include <cstddef>

#ifndef NDEBUG
#include <cassert>
#include <unordered_set>
#endif

class BlockOfInt {
    std::size_t sz;
    int* data;
public:
#ifndef NDEBUG
    static std::unordered_set<int *> alloc;
#endif
    BlockOfInt(std::size_t sz_)
        : sz(sz_), data(new int[sz_])
    {
        assert(alloc.insert(data).second);
    }
    ~BlockOfInt() {
        assert(alloc.erase(data) == 1);
        delete[] data;
    }
    int& operator[](std::size_t idx) {
        assert(alloc.count(data) == 1);
        return data[idx];
    }
    std::size_t size() const {
        assert(alloc.count(data) == 1);
        return sz;
    }
};

#endif
