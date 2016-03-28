#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

//#include "abstracttreenode.hpp"
#include "parser.hpp"
#include <stdexcept>

namespace OperationTree
{
    class Expression
    {
    public:
        Expression();
        Expression(const std::string& str);
        Expression(const char* str);
        Expression(const Expression& expr);
        Expression(AbstractTreeNode* root);
        Expression(const VarDefMap& variables);
        Expression(const FuncDefMap& functions);
        Expression(AbstractTreeNode* root, const VarDefMap& variables);
        Expression(AbstractTreeNode* root, const FuncDefMap& functions);
        Expression(const VarDefMap& variables, const FuncDefMap& functions);
        Expression(AbstractTreeNode* root, const VarDefMap& variables, const FuncDefMap& functions);
        ~Expression();

        void setVariable(const std::string& name, double value);
        void setVariables(const VarDefMap& variables);
        void setVariables(const std::vector<std::string>& names, const std::vector<double>& values);

        void setRoot(AbstractTreeNode* root);
        void setFunction(const std::string& name, int argCount, double(*func)(const std::vector<double>&));
        void setFunctions(const FuncDefMap& functions);

        void varRename(const std::vector<std::string>& oldName, const std::vector<std::string>& newName);

        const AbstractTreeNode* getRoot() const;

        double calculate() const;
    private:
        AbstractTreeNode* _root;
        VarDefMap         _variables;
        FuncDefMap        _functions;
    };
}

#endif // EXPRESSION_HPP
