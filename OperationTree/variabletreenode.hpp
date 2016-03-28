#ifndef VARIABLETREENODE_HPP
#define VARIABLETREENODE_HPP

#include <stdexcept>
#include "abstracttreenode.hpp"

namespace OperationTree
{
    class VariableTreeNode: public AbstractTreeNode
    {
    public:
        VariableTreeNode(const std::string& name);
        ~VariableTreeNode();

        /*Override*/ int getSubtype() const;
        /*Override*/ double calculate(const VarDefMap& variables, const FuncDefMap& functions) const;
        /*Override*/ AbstractTreeNode* clone() const;
        /*Override*/ void varRename(const std::vector<std::string>& oldName, const std::vector<std::string>& newName);
    private:
        std::string _name;
    };
}

#endif // VARIABLETREENODE_HPP
