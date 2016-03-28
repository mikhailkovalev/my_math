#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cmath>
#include <vector>
#include <stdexcept>
#include <sstream>

#include "mathvector.hpp"

class Matrix
{
public:
    Matrix(int size);
    double& at(int row, int column);
    const double& at(int row, int column) const;
    int size() const;
    MathVector solve(MathVector b) const;
    std::string toString() const;
private:
    static int getMainRow(int i, const std::vector<double>& A, int size);
    static void swapRows(int r1, int r2, std::vector<double>& A, MathVector& b, int size);
    static void cleanColumn(int c, std::vector<double>& A, MathVector& b, int size);

    std::vector<double> _a;
    int _size;
};

std::ostream& operator<<(std::ostream& p, const Matrix& m);

#endif // MATRIX_HPP
