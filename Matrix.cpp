#include <array>

template<class T, int rows, int cols>
class Matrix
{
    std::array<T, rows * cols> m_Data;
public:
    T& operator()(int y, int x)
    {
        return m_Data[y * cols + x];
    }

    // more methods go here
};