#include "matrix.hpp"

Matrix::Matrix(int size)
    :_size(size)
    ,_a(size * size)
{
}
double& Matrix::at(int row, int column)
{
    return _a[row * _size + column];
}
const double& Matrix::at(int row, int column) const
{
    return _a[row * _size + column];
}
int Matrix::size() const
{
    return _size;
}
MathVector Matrix::solve(MathVector b) const
{
    int mainRow;
    std::vector<double> A(_a);
    for (int i = 0; i < _size; ++i)
    {
        mainRow = getMainRow(i, A, _size);
        if (mainRow != i)
        {
            swapRows(mainRow, i, A, b, _size);
        }
        if (fabs(A[i * _size + i]) < 1e-6)
        {
            throw std::runtime_error("Singular matrix!");
        }
        cleanColumn(i, A, b, _size);
    }
    return b;
}
std::string Matrix::toString() const
{
    int i, j, n = _size - 1;
    std::stringstream ss;
    ss << "[";
    for (i = 0; i < n; ++i)
    {
        ss << "[";
        for (j = 0; j < n; ++j)
        {
            ss << at(i, j) << ", ";
        }
        ss << at(i, j) << "], ";
    }
    ss << "[";
    for (j = 0; j < n; ++j)
    {
        ss << at(i, j) << ", ";
    }
    ss << at(i, j) << "]];";
    return ss.str();
}
int Matrix::getMainRow(int i, const std::vector<double>& A, int size)
{
    int mainRow = i;
    for (int j = i + 1; j < size; ++j)
    {
        if (fabs(A[j * size + i]) > fabs(A[mainRow * size + i]))
        {
            mainRow = j;
        }
    }
    return mainRow;
}
void Matrix::swapRows(int r1, int r2, std::vector<double>& A, MathVector& b, int size)
{
    double temp;

    temp = b[r1];
    b[r1] = b[r2];
    b[r2] = temp;

    for (int i = 0; i < size; ++i)
    {
        temp = A[r1 * size + i];
        A[r1 * size + i] = A[r2 * size + i];
        A[r2 * size + i] = temp;
    }
}
void Matrix::cleanColumn(int c, std::vector<double>& A, MathVector& b, int size)
{
    int i, j;
    double factor;
    for (i = 0; i < size; ++i)
    {
        if (i != c)
        {
            factor = A[i * size + c] / A[c * size + c];
            A[i * size + c] = 0;
            b[i] -= b[c] * factor;
            for (j = c + 1; j < size; ++j)
            {
                A[i * size + j] -= factor * A[c * size + j];
            }
        }
        else
        {
            for (j = c + 1; j < size; ++j)
            {
                A[c * size + j] /= A[c * size + c];
            }
            b[c] /= A[c * size + c];
            A[c * size + c] = 1.0;
        }
    }
}
std::ostream& operator<<(std::ostream& p, const Matrix& m)
{
    p << m.toString();
    return p;
}
