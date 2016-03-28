#ifndef MATHVECTOR_HPP
#define MATHVECTOR_HPP

#include <vector>
#include <iostream>
#include <sstream>

class MathVector
{
public:
    MathVector(int dim);
    MathVector(const std::vector<double>& v);

    int dim() const;

    double& operator[](int idx);
    const double& operator[](int idx) const;

    double& at(int idx);
    const double& at(int idx) const;

    void ReplaceSegment(const MathVector& v, int BegIdx, int EndIdx = -1);
    MathVector Segment(int BegIdx, int EndIdx);

    MathVector operator + (const MathVector& rhs) const;
    MathVector operator - (const MathVector& rhs) const;
    MathVector operator * (double rhs) const;
    MathVector operator / (double rhs) const;

    MathVector operator += (const MathVector& rhs);
    MathVector operator -= (const MathVector& rhs);
    MathVector operator *= (double);
    MathVector operator /= (double);

    std::string toStdString() const;
    const std::vector<double>& toStdVector() const;
private:
    std::vector<double> _v;
};

MathVector operator*(double lhs, const MathVector& rhs);
std::ostream& operator << (std::ostream& p, const MathVector& v);

#endif //MATHVECTOR_HPP

