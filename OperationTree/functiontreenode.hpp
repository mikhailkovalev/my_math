#ifndef FUNCTIONTREENODE_HPP
#define FUNCTIONTREENODE_HPP

#include <stdexcept>
#include "abstracttreenode.hpp"

namespace OperationTree
{
    class FunctionTreeNode: public AbstractTreeNode
    {
    public:
        FunctionTreeNode(const std::string& name);
        ~FunctionTreeNode();

        void addArg(AbstractTreeNode* arg);

        /*Override*/ int getSubtype() const;
        /*Override*/ double calculate(const VarDefMap& variables, const FuncDefMap& functions) const;
        /*Override*/ AbstractTreeNode* clone() const;
        /*Override*/ void varRename(const std::vector<std::string>& oldName, const std::vector<std::string>& newName);

    private:
        std::string _name;
        std::vector<AbstractTreeNode*> _args;
    };
}

#endif // FUNCTIONTREENODE_HPP
