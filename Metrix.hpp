#include <vector>

template<typename T>
class Matrix
{
public:
    Matrix(std::vector<T> data, unsigned dim) : mData(std::move(data)), mDimensions(dim) {}

    T& operator[] (size_t i)
    {
        return mData + i * mDimensions;
    }

private:
    std::vector<T> mData;
    unsigned mDimensions;
};
