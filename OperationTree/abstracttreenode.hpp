#ifndef ABSTRACTTREENODE_HPP
#define ABSTRACTTREENODE_HPP

#include <map>
#include <string>
#include <vector>

namespace OperationTree
{
    typedef std::map<std::string, double> VarDefMap;
    typedef std::map<std::string, std::pair<int, double(*)(const std::vector<double>&)> > FuncDefMap;

    class AbstractTreeNode
    {
    public:
        enum Type {BINARY_OPERATOR, UNARY_OPERATOR, NUMBER, VARIABLE, FUNCTION};

        AbstractTreeNode(Type type);
        virtual ~AbstractTreeNode();

        int getType() const;

        virtual int getSubtype() const = 0;
        virtual double calculate(const VarDefMap& variables, const FuncDefMap& functions) const = 0;
        virtual AbstractTreeNode* clone() const = 0;
        virtual void varRename(const std::vector<std::string>& oldName, const std::vector<std::string>& newName) = 0;
    protected:
        static const double epsilon;
        Type _type;
    };
}

#endif // ABSTRACTTREENODE_HPP
