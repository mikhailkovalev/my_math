#include "unaryoperatortreenode.hpp"
using namespace OperationTree;

UnaryOperatorTreeNode::UnaryOperatorTreeNode(Subtype subtype)
    :AbstractTreeNode(AbstractTreeNode::UNARY_OPERATOR)
    ,_subtype(subtype)
    ,_arg(0)
{
}

UnaryOperatorTreeNode::~UnaryOperatorTreeNode()
{
    if (_arg) delete _arg;
}

void UnaryOperatorTreeNode::setArg(AbstractTreeNode* arg)
{
    if (_arg) delete _arg;
    _arg = arg;
}

int UnaryOperatorTreeNode::getSubtype() const
{
    return _subtype;
}

double UnaryOperatorTreeNode::calculate(const VarDefMap& variables, const FuncDefMap& functions) const
{
    switch(_subtype)
    {
    case MINUS:
        return -_arg -> calculate(variables, functions);
    case FACTORIAL:
        return tgamma(1.0 + _arg -> calculate(variables, functions));
    }
    return 0;
}

AbstractTreeNode* UnaryOperatorTreeNode::clone() const
{
    UnaryOperatorTreeNode* p = new UnaryOperatorTreeNode(_subtype);
    if (_arg) p -> setArg(_arg -> clone());
    return p;
}

void UnaryOperatorTreeNode::varRename(const std::vector<std::string>& oldName, const std::vector<std::string>& newName)
{
    if (_arg) _arg -> varRename(oldName, newName);
}
