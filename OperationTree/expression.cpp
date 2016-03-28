#include "expression.hpp"
using namespace OperationTree;

Expression::Expression()
    :_root(0)
{
}

Expression::Expression(const std::string& str)
    :_root(Parser::Parse(str))
{
}

Expression::Expression(const char* str)
    :_root(Parser::Parse(std::string(str)))
{
}

Expression::Expression(const Expression& expr)
    :_root(expr._root -> clone())
    ,_variables(expr._variables)
    ,_functions(expr._functions)
{
}

Expression::Expression(AbstractTreeNode* root)
    :_root(root)
{
}

Expression::Expression(const VarDefMap& variables)
    :_root(0)
    ,_variables(variables)
{
}

Expression::Expression(const FuncDefMap& functions)
    :_root(0)
    ,_functions(functions)
{
}

Expression::Expression(AbstractTreeNode* root, const VarDefMap& variables)
    :_root(root)
    ,_variables(variables)
{
}

Expression::Expression(AbstractTreeNode* root, const FuncDefMap& functions)
    :_root(root)
    ,_functions(functions)
{
}

Expression::Expression(const VarDefMap& variables, const FuncDefMap& functions)
    :_root(0)
    ,_variables(variables)
    ,_functions(functions)
{
}

Expression::Expression(AbstractTreeNode* root, const VarDefMap& variables, const FuncDefMap& functions)
    :_root(root)
    ,_variables(variables)
    ,_functions(functions)
{
}

Expression::~Expression()
{
    if (_root) delete _root;
}

void Expression::setRoot(AbstractTreeNode* root)
{
    if (_root) delete _root;
    _root = root;
}

void Expression::setVariable(const std::string& name, double value)
{
    VarDefMap::iterator lb = _variables.lower_bound(name);

    if (lb != _variables.end() && !(_variables.key_comp()(name, lb -> first)))
    {
        lb -> second = value;
    }
    else
    {
        _variables.insert(lb, std::make_pair(name, value));
    }
}

void Expression::setVariables(const VarDefMap& variables)
{
    VarDefMap::const_iterator i = variables.begin();

    for (; i != variables.end(); ++i)
    {
        setVariable(i -> first, i -> second);
    }
}

void Expression::setVariables(const std::vector<std::string>& names, const std::vector<double>& values)
{
    int size = names.size();
    if (size != values.size())
    {
        throw std::runtime_error("Name-list and values-list must be same size!");
    }
    for (int i = 0; i < size; ++i)
    {
        setVariable(names[i], values[i]);
    }
}

void Expression::setFunction(const std::string& name, int argCount, double(*func)(const std::vector<double>&))
{
    FuncDefMap::iterator lb = _functions.lower_bound(name);

    if (lb != _functions.end() && !(_functions.key_comp()(name, lb -> first)))
    {
        lb -> second = std::make_pair(argCount, func);
    }
    else
    {
        _functions.insert(lb, std::make_pair(name, std::make_pair(argCount, func)));
    }
}

void Expression::setFunctions(const FuncDefMap& functions)
{
    FuncDefMap::const_iterator i = functions.begin();

    for (; i != functions.end(); ++i)
    {
        setFunction(i -> first, i -> second.first, i -> second.second);
    }
}

void Expression::varRename(const std::vector<std::string>& oldName, const std::vector<std::string>& newName)
{
    if (_root) _root -> varRename(oldName, newName);
}

const AbstractTreeNode* Expression::getRoot() const
{
    return _root;
}

double Expression::calculate() const
{
    return _root ? _root -> calculate(_variables, _functions) : 0;
}
