#include "variabletreenode.hpp"
using namespace OperationTree;

VariableTreeNode::VariableTreeNode(const std::string& name)
    :AbstractTreeNode(AbstractTreeNode::VARIABLE)
    ,_name(name)
{
}

VariableTreeNode::~VariableTreeNode()
{
}

int VariableTreeNode::getSubtype() const
{
    return 0;
}

double VariableTreeNode::calculate(const VarDefMap& variables, const FuncDefMap& functions) const
{
    VarDefMap::const_iterator it = variables.find(_name);

    if (it == variables.end())
    {
        std::string err = "Unknown variable \"";
        err += _name;
        err += "\"!";
        throw std::runtime_error(err);
    }

    return it -> second;
}

AbstractTreeNode* VariableTreeNode::clone() const
{
    return new VariableTreeNode(_name);
}

void VariableTreeNode::varRename(const std::vector<std::string>& oldName, const std::vector<std::string>& newName)
{
    int i, n = oldName.size();
    for (i = 0; i < n; ++i)
    {
        if (oldName[i] == _name) break;
    }

    if (i != n)
    {
        _name = newName[i];
    }
}
