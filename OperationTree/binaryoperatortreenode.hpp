#ifndef BINARYOPERATORTREENODE_HPP
#define BINARYOPERATORTREENODE_HPP

#include <cmath>
#include <stdexcept>
#include "abstracttreenode.hpp"

namespace OperationTree
{
    class BinaryOperatorTreeNode: public AbstractTreeNode
    {
    public:
        enum Subtype {PLUS, MINUS, ASTERISK, SLASH, CIRCUMFLEX};

        BinaryOperatorTreeNode(Subtype subtype);
        ~BinaryOperatorTreeNode();

        void setLhs(AbstractTreeNode* arg);
        void setRhs(AbstractTreeNode* arg);

        /*Override*/ int getSubtype() const;
        /*Override*/ double calculate(const VarDefMap& variables, const FuncDefMap& functions) const;
        /*Override*/ AbstractTreeNode* clone() const;
        /*Override*/ void varRename(const std::vector<std::string>& oldName, const std::vector<std::string>& newName);

    private:
        Subtype _subtype;
        AbstractTreeNode* _lhs;
        AbstractTreeNode* _rhs;
    };

    double pow(double, int);
}

#endif // BINARYOPERATORTREENODE_HPP
