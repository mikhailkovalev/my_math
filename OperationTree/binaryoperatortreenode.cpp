#include "binaryoperatortreenode.hpp"
using namespace OperationTree;

BinaryOperatorTreeNode::BinaryOperatorTreeNode(Subtype subtype)
    :AbstractTreeNode(AbstractTreeNode::BINARY_OPERATOR)
    ,_subtype(subtype)
    ,_lhs(0)
    ,_rhs(0)
{
}

BinaryOperatorTreeNode::~BinaryOperatorTreeNode()
{
    if (_lhs) delete _lhs;
    if (_rhs) delete _rhs;
}

void BinaryOperatorTreeNode::setLhs(AbstractTreeNode* arg)
{
    if (_lhs) delete _lhs;
    _lhs = arg;
}

void BinaryOperatorTreeNode::setRhs(AbstractTreeNode* arg)
{
    if (_rhs) delete _rhs;
    _rhs = arg;
}

int BinaryOperatorTreeNode::getSubtype() const
{
    return _subtype;
}

double BinaryOperatorTreeNode::calculate(const VarDefMap& variables, const FuncDefMap& functions) const
{
    double lhs = _lhs -> calculate(variables, functions);
    double rhs = _rhs -> calculate(variables, functions);
    switch(_subtype)
    {
    case PLUS:
        return lhs + rhs;
    case MINUS:
        return lhs - rhs;
    case ASTERISK:
        return lhs * rhs;
    case SLASH:
        if (fabs(rhs) < epsilon)
        {
            throw std::runtime_error("Divide by zero!");
        }
        return lhs / rhs;
    case CIRCUMFLEX:
        if (fabs(lhs) < epsilon && fabs(rhs) < epsilon)
        {
            throw std::runtime_error("Zero to the power of zero!");
        }
        if (fabs(rhs - (int)rhs) < epsilon)
        {
            return OperationTree::pow(lhs, rhs);
        }
        if (lhs < 0)
        {
            throw std::runtime_error("Negative to the power!");
        }
        return pow(lhs, rhs);
    }
    return 0;
}

AbstractTreeNode* BinaryOperatorTreeNode::clone() const
{
    BinaryOperatorTreeNode* p = new BinaryOperatorTreeNode(_subtype);

    if (_lhs) p -> setLhs(_lhs -> clone());
    if (_rhs) p -> setRhs(_rhs -> clone());

    return p;
}

void BinaryOperatorTreeNode::varRename(const std::vector<std::string>& oldName, const std::vector<std::string>& newName)
{
    if (_lhs) _lhs -> varRename(oldName, newName);
    if (_rhs) _rhs -> varRename(oldName, newName);
}

double OperationTree::pow(double a, int b)
{
    double res = 1.0;
    while (b)
    {
        if (b & 1)
        {
            res *= a;
        }
        a *= a;
        b >>= 1;
    }
    return res;
}
