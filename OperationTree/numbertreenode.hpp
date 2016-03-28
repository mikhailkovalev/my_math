#ifndef NUMBERTREENODE_HPP
#define NUMBERTREENODE_HPP

#include "abstracttreenode.hpp"

namespace OperationTree
{
    class NumberTreeNode: public AbstractTreeNode
    {
    public:
        NumberTreeNode(double value);
        ~NumberTreeNode();

        /*Override*/ int getSubtype() const;
        /*Override*/ double calculate(const VarDefMap& variables, const FuncDefMap& functions) const;
        /*Override*/ AbstractTreeNode* clone() const;
        /*Override*/ void varRename(const std::vector<std::string>& oldName, const std::vector<std::string>& newName);
    private:
        double _value;
    };
}

#endif // NUMBERTREENODE_HPP
