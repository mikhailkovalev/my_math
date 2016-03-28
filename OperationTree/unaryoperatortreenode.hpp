#ifndef UNARYOPERATORTREENODE_HPP
#define UNARYOPERATORTREENODE_HPP

#include <cmath>
#include "abstracttreenode.hpp"

namespace OperationTree
{
    class UnaryOperatorTreeNode: public AbstractTreeNode
    {
    public:
        enum Subtype {MINUS, FACTORIAL};

        UnaryOperatorTreeNode(Subtype subtype);
        ~UnaryOperatorTreeNode();

        void setArg(AbstractTreeNode* arg);

        /*Override*/ int getSubtype() const;
        /*Override*/ double calculate(const VarDefMap& variables, const FuncDefMap& functions) const;
        /*Override*/ AbstractTreeNode* clone() const;
        /*Override*/ void varRename(const std::vector<std::string>& oldName, const std::vector<std::string>& newName);
    private:
        Subtype _subtype;
        AbstractTreeNode* _arg;
    };
}

#endif // UNARYOPERATORTREENODE_HPP
