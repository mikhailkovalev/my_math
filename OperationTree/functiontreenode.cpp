#include "functiontreenode.hpp"
using namespace OperationTree;

FunctionTreeNode::FunctionTreeNode(const std::string& name)
    :AbstractTreeNode(AbstractTreeNode::FUNCTION)
    ,_name(name)
{
}

FunctionTreeNode::~FunctionTreeNode()
{
    int n = _args.size();
    for (int i = 0; i < n; ++i)
    {
        if (_args[i]) delete _args[i];
    }
}

void FunctionTreeNode::addArg(AbstractTreeNode* arg)
{
    if (arg) _args.push_back(arg);
}

int FunctionTreeNode::getSubtype() const
{
    return 0;
}

double FunctionTreeNode::calculate(const VarDefMap& variables, const FuncDefMap& functions) const
{
    FuncDefMap::const_iterator it = functions.find(_name);

    if (it == functions.end())
    {
        std::string err = "Unknown function \"";
        err += _name;
        err += "\"!";
        throw std::runtime_error(err);
    }

    FuncDefMap::mapped_type pr = it -> second;

    if (pr.first != -1 && pr.first != _args.size())
    {
        std::string err = "Invalid number of arguments for function \"";
        err += _name;
        err += "\"!";
        throw std::runtime_error(err);
    }

    int argCount = _args.size();
    std::vector<double> argValues;
    argValues.reserve(argCount);

    for (int i = 0; i < argCount; ++i)
    {
        argValues.push_back(_args[i] -> calculate(variables, functions));
    }

    return (pr.second)(argValues);
}

AbstractTreeNode* FunctionTreeNode::clone() const
{
    FunctionTreeNode* p = new FunctionTreeNode(_name);

    std::vector<AbstractTreeNode*>::const_iterator i = _args.begin();
    for (; i != _args.end(); ++i)
    {
        p -> addArg((*i) -> clone());
    }
    return p;
}

void FunctionTreeNode::varRename(const std::vector<std::string>& oldName, const std::vector<std::string>& newName)
{
    std::vector<AbstractTreeNode*>::iterator it = _args.begin();
    for (; it != _args.end(); ++it)
    {
        (*it) -> varRename(oldName, newName);
    }
}
