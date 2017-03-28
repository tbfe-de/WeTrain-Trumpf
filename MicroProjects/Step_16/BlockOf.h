#ifndef BlockOf
#define BlockOf_H

#include <cstddef>

template<typename T>
class BlockOf {
    T* data;
public:
    BlockOf()
        : data(nullptr)
    {}
    BlockOf(const T& init)
        : data(new T(init))
    {}
    ~BlockOf() {
        delete data;
    }
    BlockOf(const BlockOf&) = delete;
    BlockOf& operator=(const BlockOf&) = delete;
    BlockOf(BlockOf&& init)
        : data(init.data) {
        init.data = nullptr;
    }
    BlockOf& operator=(BlockOf&& rhs) {
        if (data != rhs.data) {
            delete data;
            data = rhs.data;
            rhs.data = nullptr;
        }
        return *this;
    }
    T& get() {
        return *data;
    }
    const T& get() const {
        return *data;
    }
    bool empty() const {
        return (data == nullptr);
    }
    void swap(BlockOf& other) {
        const auto tmp_data = data;
        data = other.data;
        other.data = tmp_data;
    }
};

#endif
