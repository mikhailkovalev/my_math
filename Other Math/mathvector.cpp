#include "mathvector.hpp"

MathVector::MathVector(int dim)
    :_v(dim)
{
}

MathVector::MathVector(const std::vector<double>& v)
    :_v(v)
{
}

int MathVector::dim() const
{
    return _v.size();
}

double& MathVector::operator[](int idx)
{
    return _v.at(idx);
}

const double& MathVector::operator[](int idx) const
{
    return _v.at(idx);
}

double& MathVector::at(int idx)
{
    return _v.at(idx);
}

const double& MathVector::at(int idx) const
{
    return _v.at(idx);
}

void MathVector::ReplaceSegment(const MathVector& v, int BegIdx, int EndIdx)
{
    if (EndIdx == -1) EndIdx = BegIdx + v.dim();
    for (int i = BegIdx; i < EndIdx; ++i)
    {
        _v[i] = v[i - BegIdx];
    }
}

MathVector MathVector::Segment(int BegIdx, int EndIdx)
{
    std::vector<double> res(_v.begin() + BegIdx, _v.begin() + EndIdx);
    return MathVector(res);
}

MathVector MathVector::operator+(const MathVector& rhs) const
{
    if (_v.size() != rhs._v.size())
    {
        throw 0;
    }
    int i, n = _v.size();
    MathVector res(n);

    for (i = 0; i < n; ++i)
    {
        res._v[i] = _v[i] + rhs._v[i];
    }
    return res;
}

MathVector MathVector::operator-(const MathVector& rhs) const
{
    if (_v.size() != rhs._v.size())
    {
        throw 0;
    }
    int i, n = _v.size();
    MathVector res(n);

    for (i = 0; i < n; ++i)
    {
        res._v[i] = _v[i] - rhs._v[i];
    }
    return res;
}

MathVector MathVector::operator*(double rhs) const
{
    int i, n = _v.size();
    MathVector res(n);

    for (i = 0; i < n; ++i)
    {
        res._v[i] = _v[i] * rhs;
    }
    return res;
}

MathVector MathVector::operator / (double rhs) const
{
    double factor = 1.0 / rhs;
    int i, n = _v.size();
    MathVector res(n);

    for (i = 0; i < n; ++i)
    {
        res._v[i] = _v[i] * factor;
    }
    return res;
}

MathVector MathVector::operator += (const MathVector& rhs)
{
    int n = _v.size();
    if (n != rhs._v.size()) throw 0;
    for (int i = 0; i < n; ++i)
    {
        _v[i] += rhs._v[i];
    }
    return *this;
}

MathVector MathVector::operator -= (const MathVector& rhs)
{
    int n = _v.size();
    if (n != rhs._v.size()) throw 0;
    for (int i = 0; i < n; ++i)
    {
        _v[i] -= rhs._v[i];
    }
    return *this;
}

MathVector MathVector::operator *= (double rhs)
{
    int i, n = _v.size();
    for (i = 0; i < n; ++i)
    {
        _v[i] *= rhs;
    }
    return *this;
}

MathVector MathVector::operator /= (double rhs)
{
    double factor = 1.0 / rhs;
    int i, n = _v.size();
    for (i = 0; i < n; ++i)
    {
        _v[i] *= factor;
    }
    return *this;
}

MathVector operator*(double lhs, const MathVector& rhs)
{
    return rhs * lhs;
}

std::string MathVector::toStdString() const
{
    int i, n = _v.size() - 1;
    std::stringstream ss;
    ss << "(";
    for (i = 0; i < n; ++i)
    {
        ss << _v[i] << ", ";
    }
    ss << _v[i] << ")";
    return ss.str();
}

const std::vector<double>& MathVector::toStdVector() const
{
    return _v;
}

std::ostream& operator << (std::ostream& p, const MathVector& v)
{
    p << v.toStdString();
    return p;
}

