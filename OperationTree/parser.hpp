#ifndef PARSER_HPP
#define PARSER_HPP

#include "binaryoperatortreenode.hpp"
#include "expression.hpp"
#include "functiontreenode.hpp"
#include "numbertreenode.hpp"
#include "unaryoperatortreenode.hpp"
#include "variabletreenode.hpp"

namespace OperationTree
{
    class Parser
    {
    public:
        static AbstractTreeNode* Parse(const std::string& str);

    private:
        enum Type{NONE, ID, DELIMITER, NUMBER};

        static void getToken();
        static void getNumber();
        static void getID();

        static bool isDelim(char c);

        static AbstractTreeNode* Expr();
        static AbstractTreeNode* Pre_Unary();
        static AbstractTreeNode* Term();
        static AbstractTreeNode* Exp();
        static AbstractTreeNode* Post_Unary();
        static AbstractTreeNode* Factor();
        static AbstractTreeNode* Func_Call(const std::string& name);

        static std::string::const_iterator p;
        static std::string::const_iterator end;

        static std::string currentToken;
        static Type currentType;
    };
}

#endif // PARSER_HPP
