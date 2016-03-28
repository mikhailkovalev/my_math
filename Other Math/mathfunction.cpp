#include "mathfunction.hpp"

MathFunction::MathFunction(const Expression& expr, const std::vector<std::string>& names)
    :_names(names)
    ,_expr(expr)
{
    addFunctions(&_expr);
    removeClone();
}

MathFunction::MathFunction(const std::string& expr, const std::vector<std::string>& names)
    :_names(names)
    ,_expr(expr)
{
    addFunctions(&_expr);
    removeClone();
}

MathFunction::MathFunction(const char* expr, const std::vector<std::string>& names)
    :_names(names)
    ,_expr(expr)
{
    addFunctions(&_expr);
    removeClone();
}

MathFunction::MathFunction(const std::string& expr, int var_count, ...)
    :_expr(expr)
{
    addFunctions(&_expr);

    _names.reserve(var_count);

    va_list argPtr;
    va_start(argPtr, var_count);
    for (int i = 0; i < var_count; ++i)
    {
        _names.push_back(std::string(va_arg(argPtr, const char*)));
    }
    va_end(argPtr);
    removeClone();
}

double MathFunction::operator()(const MathVector& x)
{
    _expr.setVariables(_names, x.toStdVector());
    return _expr.calculate();
}

double MathFunction::operator()(double x, ...)
{
    int n = _names.size();
    std::vector<double> values;
    values.reserve(n);

    values.push_back(x);

    va_list argPtr;
    va_start(argPtr, x);

    for (int i = 1; i < n; ++i)
    {
        values.push_back(va_arg(argPtr, double));
    }

    va_end(argPtr);

    _expr.setVariables(_names, values);
    return _expr.calculate();
}

double MathFunction::rect_int(int step_count, ...)
{
    int i, j, n = _names.size();
    std::vector<double> low;
    std::vector<double> high;

    low.reserve(n);
    high.reserve(n);

    va_list arg_ptr;
    va_start(arg_ptr, step_count);

    for (i = 0; i < n; ++i)
    {
        low.push_back(va_arg(arg_ptr, double));
        high.push_back(va_arg(arg_ptr, double));
    }

    va_end(arg_ptr);

    std::vector<int> idx(n, 0);
    std::vector<double> val(low.begin(), low.end());

    double sum = 0;
    double term;

    while (true)
    {
        term = (*this)(val);
        for (j = 0; j < n; ++j)
        {
            term *= (high[j] - low[j]) / (6 * step_count) *
            (idx[j] == 0 || idx[j] == 2 * step_count
            ? 1. : idx[j] % 2 == 0 ? 2. : 4.);
        }
        sum += term;

        for (j = n - 1; j >= 0 && idx[j] == 2 * step_count; --j);

        if (j == -1) break;
        ++idx[j];
        for (j = j + 1; j < n; ++j) idx[j] = 0;

        for (j = 0; j < n; ++j)
        {
            val[j] = low[j] + (high[j] - low[j]) * idx[j] / (2 * step_count);
        }
    }

    return sum;
}

MathFunction MathFunction::operator *(const MathFunction& rhs) const
{
    std::vector<std::string> names;
    MergeVars(_names, rhs._names, names);

    BinaryOperatorTreeNode* op = new BinaryOperatorTreeNode(BinaryOperatorTreeNode::ASTERISK);
    op -> setLhs(_expr.getRoot() -> clone());
    op -> setRhs(rhs._expr.getRoot() -> clone());
    Expression expr;
    expr.setRoot(op);
    return MathFunction(expr, names);
}
MathFunction MathFunction::operator +(const MathFunction& rhs) const
{
    std::vector<std::string> names;
    MergeVars(_names, rhs._names, names);

    BinaryOperatorTreeNode* op = new BinaryOperatorTreeNode(BinaryOperatorTreeNode::PLUS);
    op -> setLhs(_expr.getRoot() -> clone());
    op -> setRhs(rhs._expr.getRoot() -> clone());

    Expression expr;
    expr.setRoot(op);
    return MathFunction(expr, names);
}

MathFunction MathFunction::operator -(const MathFunction& rhs) const
{
    std::vector<std::string> names;
    MergeVars(_names, rhs._names, names);

    BinaryOperatorTreeNode* op = new BinaryOperatorTreeNode(BinaryOperatorTreeNode::MINUS);
    op -> setLhs(_expr.getRoot() -> clone());
    op -> setRhs(rhs._expr.getRoot() -> clone());

    Expression expr;
    expr.setRoot(op);
    return MathFunction(expr, names);
}

MathFunction MathFunction::operator /(const MathFunction& rhs) const
{
    std::vector<std::string> names;
    MergeVars(_names, rhs._names, names);

    BinaryOperatorTreeNode* op = new BinaryOperatorTreeNode(BinaryOperatorTreeNode::SLASH);
    op -> setLhs(_expr.getRoot() -> clone());
    op -> setRhs(rhs._expr.getRoot() -> clone());

    Expression expr;
    expr.setRoot(op);
    return MathFunction(expr, names);
}



void MathFunction::varRename(const std::vector<std::string>& oldName, const std::vector<std::string>& newName)
{
    _expr.varRename(oldName, newName);

    int i, j;
    for (i = 0; i < _names.size(); ++i)
    {
        for (j = 0; j < oldName.size(); ++j)
        {
            if (_names[i] == oldName[j]) _names[i] = newName[j];
        }
    }
    removeClone();
}

void MathFunction::varRename(const std::string& oldName, const std::string& newName)
{
    std::vector<std::string> on(1, oldName);
    std::vector<std::string> nn(1, newName);
    varRename(on, nn);
}

int MathFunction::arg_count() const
{
    return _names.size();
}

void MathFunction::removeClone()
{
    int i, j;

    for (i = 0; i < _names.size(); ++i)
    {
        for (j = i + 1; j < _names.size(); ++j)
        {
            if (_names[i] == _names[j]) _names.erase(_names.begin() + j);
        }
    }
}

void MathFunction::MergeVars(const std::vector<std::string>& lst1, const std::vector<std::string>& lst2, std::vector<std::string>& lst3)
{
    lst3.reserve(lst1.size() + lst2.size());
    bool first;

    if (lst1.size() >= lst2.size())
    {
        lst3.assign(lst1.begin(), lst1.end());
        first = false;
    }
    else
    {
        lst3.assign(lst2.begin(), lst2.end());
        first = true;
    }

    const std::vector<std::string>* oth = first ? &lst1 : &lst2;

    for (int i = 0; i < oth -> size(); ++i)
    {
        if (std::find(lst3.begin(), lst3.end(), oth -> at(i)) == lst3.end())
        {
            lst3.push_back(oth -> at(i));
        }
    }
}
