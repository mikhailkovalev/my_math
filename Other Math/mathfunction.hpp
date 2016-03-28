#ifndef MATHFUNCTION_HPP
#define MATHFUNCTION_HPP

#include <vector>
#include <string>
#include "mathvector.hpp"
#include "basic_functions.hpp"
#include <cstdarg>
#include <binaryoperatortreenode.hpp>
//#include "OperationTree\expression.hpp"
using namespace OperationTree;

class MathFunction
{
public:
    MathFunction(const Expression& expr, const std::vector<std::string>& names);
    MathFunction(const std::string& expr, const std::vector<std::string>& names);
    MathFunction(const char* expr, const std::vector<std::string>& names);
    MathFunction(const std::string& expr, int var_count, ...);

    double operator()(const MathVector& x);
    double operator()(double x, ...);

    double rect_int(int step_count, ...);

    MathFunction operator *(const MathFunction& rhs) const;
    MathFunction operator +(const MathFunction& rhs) const;
    MathFunction operator -(const MathFunction& rhs) const;
    MathFunction operator /(const MathFunction& rhs) const;



    void varRename(const std::vector<std::string>& oldName, const std::vector<std::string>& newName);
    void varRename(const std::string& oldName, const std::string& newName);

    int arg_count() const;
private:
    void removeClone();
    static void MergeVars(const std::vector<std::string>& lst1, const std::vector<std::string>& lst2, std::vector<std::string>& res);

    std::vector<std::string> _names;
    Expression _expr;
};

#endif //MATHFUNCTION_HPP
