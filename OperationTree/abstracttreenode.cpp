#include "abstracttreenode.hpp"
using namespace OperationTree;

const double AbstractTreeNode::epsilon = 1e-8;

AbstractTreeNode::AbstractTreeNode(Type type)
    :_type(type)
{
}

AbstractTreeNode::~AbstractTreeNode()
{
}

int AbstractTreeNode::getType() const
{
    return _type;
}
