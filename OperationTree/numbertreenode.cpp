#include "numbertreenode.hpp"
using namespace OperationTree;

NumberTreeNode::NumberTreeNode(double value)
    :AbstractTreeNode(AbstractTreeNode::NUMBER)
    ,_value(value)
{
}

NumberTreeNode::~NumberTreeNode()
{
}

int NumberTreeNode::getSubtype() const
{
    return 0;
}

double NumberTreeNode::calculate(const VarDefMap& variables, const FuncDefMap& functions) const
{
    return _value;
}

AbstractTreeNode* NumberTreeNode::clone() const
{
    return new NumberTreeNode(_value);
}

void NumberTreeNode::varRename(const std::vector<std::string>& oldName, const std::vector<std::string>& newName)
{
}
