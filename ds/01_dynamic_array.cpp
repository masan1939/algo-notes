// 01. 动态数组（手写 vector 的核心逻辑）

#include <iostream>
#include <stdexcept>

class DynArray {
public:
    DynArray() : data_(nullptr), size_(0), cap_(0) {}
    ~DynArray() { delete[] data_; }

    // 禁止浅拷贝
    DynArray(const DynArray&) = delete;
    DynArray& operator=(const DynArray&) = delete;

    void push_back(int v) {
        if (size_ == cap_) grow();
        data_[size_++] = v;
    }

    int& operator[](int i) {
        if (i < 0 || i >= size_) throw std::out_of_range("index");
        return data_[i];
    }

    int size() const { return size_; }
    int capacity() const { return cap_; }

private:
    void grow() {
        int newCap = cap_ == 0 ? 1 : cap_ * 2;
        int* p = new int[newCap];
        for (int i = 0; i < size_; ++i) p[i] = data_[i];
        delete[] data_;
        data_ = p;
        cap_ = newCap;
    }

    int* data_;
    int size_;
    int cap_;
};

int main() {
    DynArray a;
    for (int i = 1; i <= 10; ++i) a.push_back(i);
    for (int i = 0; i < a.size(); ++i) std::cout << a[i] << ' ';
    std::cout << "\nsize=" << a.size() << " cap=" << a.capacity() << '\n';
    return 0;
}
