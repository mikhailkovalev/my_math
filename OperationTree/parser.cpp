#include "parser.hpp"
using namespace OperationTree;

std::string::const_iterator Parser::p;
std::string::const_iterator Parser::end;
std::string                 Parser::currentToken;
Parser::Type                Parser::currentType = Parser::NONE;

AbstractTreeNode* Parser::Parse(const std::string& str)
{
    p = str.begin();
    end = str.end();

    getToken();
    return Expr();
}

void Parser::getToken()
{
    currentToken = "";
    currentType = NONE;

    if (p == end) return;

    while(p != end && isspace(*p))
    {
        ++p;
    }

    if (p == end) return;

    //std::cout << "skiped white\n";

    if (isdigit(*p) || *p == '.')
    {
        getNumber();
        currentType = NUMBER;
    }
    else if (isalpha(*p))
    {
        getID();
        currentType = ID;
    }
    else /*if (isDelim(*p))*/
    {
        currentToken += (*p);
        ++p;
        currentType = DELIMITER;
    }
}

void Parser::getNumber()
{
    bool hasPoint = (*p == '.');
    do
    {
        currentToken += *p;
        ++p;
        if (hasPoint && *p == '.') break;
    }
    while(p != end && (isdigit(*p) || *p == '.'));
}

void Parser::getID()
{
    while (p != end && !isDelim(*p))
    {
        currentToken += (*p);
        ++p;
    }
}

bool Parser::isDelim(char c)
{
    return !isalnum(c) || c == '_';
}

AbstractTreeNode* Parser::Expr()
{
    AbstractTreeNode* res = Pre_Unary();
    BinaryOperatorTreeNode* op = 0;

    char opChar = '\0';
    while (currentType == DELIMITER && ((opChar = currentToken[0]) == '+' || opChar == '-'))
    {
        getToken();
        if (currentType == NONE)
        {
            delete res;
            throw std::runtime_error("Unexpected end of line!");
        }

        op = new BinaryOperatorTreeNode(opChar == '+' ? BinaryOperatorTreeNode::PLUS
                                                      : BinaryOperatorTreeNode::MINUS);
        op -> setLhs(res);
        try
        {
            res = Term();
        }
        catch(std::runtime_error e)
        {
            delete op;
            throw e;
        }
        op -> setRhs(res);
        res = op;
    }
    return res;
}

AbstractTreeNode* Parser::Pre_Unary()
{
    bool isNegative = false;
    char opChar = '\0';
    if (currentType == DELIMITER && ((opChar = currentToken[0]) == '+' || opChar == '-'))
    {
        isNegative = opChar == '-';
        getToken();
        if (currentType == NONE)
        {
            throw std::runtime_error("Unexpected end of line!");
        }
        //std::cout << "\nRet to Pre_Unary in if\n";
    }
    AbstractTreeNode* res = Term();
    if (isNegative)
    {
        UnaryOperatorTreeNode* op = new UnaryOperatorTreeNode(UnaryOperatorTreeNode::MINUS);
        op -> setArg(res);
        res = op;
    }
    return res;
}

AbstractTreeNode* Parser::Term()
{
    char opChar = '\0';
    AbstractTreeNode* res = Exp();
    BinaryOperatorTreeNode* op = 0;
    while(currentType == DELIMITER && ((opChar = currentToken[0]) == '*' || opChar == '/'))
    {
        getToken();
        if (currentType == NONE)
        {
            delete res;
            throw std::runtime_error("Unexpected end of line!");
        }

        op = new BinaryOperatorTreeNode(opChar == '*' ? BinaryOperatorTreeNode::ASTERISK : BinaryOperatorTreeNode::SLASH);
        op -> setLhs(res);

        try
        {
            res = Exp();
        }
        catch(std::runtime_error e)
        {
            delete op;
            throw e;
        }

        op -> setRhs(res);
        res = op;
    }
    return res;
}

AbstractTreeNode* Parser::Exp()
{
    AbstractTreeNode* res = Post_Unary();
    if (currentType == DELIMITER && currentToken[0] == '^')
    {
        BinaryOperatorTreeNode* op = new BinaryOperatorTreeNode(BinaryOperatorTreeNode::CIRCUMFLEX);
        op -> setLhs(res);
        getToken();
        if (currentType == NONE)
        {
            delete op;
            throw std::runtime_error("Unexpected end of line!");
        }
        try
        {
            res = Post_Unary();
        }
        catch(std::runtime_error e)
        {
            delete op;
            throw e;
        }
        op -> setRhs(res);
        res = op;
    }
    return res;
}

AbstractTreeNode* Parser::Post_Unary()
{
    AbstractTreeNode* res = Factor();
    if (currentType == DELIMITER && currentToken[0] == '!')
    {
        UnaryOperatorTreeNode* op = new UnaryOperatorTreeNode(UnaryOperatorTreeNode::FACTORIAL);
        op -> setArg(res);
        res = op;
        getToken();
    }
    return res;
}

AbstractTreeNode* Parser::Factor()
{
    switch(currentType)
    {
    case NUMBER:
        {
            double number;
            sscanf(currentToken.c_str(), "%lf", &number);
            getToken();

            return new NumberTreeNode(number);
        }
        break;
    case ID:
        {
            std::string name = currentToken;
            getToken();
            if (currentType == DELIMITER && currentToken[0] == '(')
            {
                AbstractTreeNode* res = Func_Call(name);
                return res;
            }
            else
            {
                return new VariableTreeNode(name);
            }
        }
        break;
    case DELIMITER:
        {
            if (currentType == DELIMITER && currentToken[0] == '(')
            {
                getToken();
                if (currentType == NONE)
                {
                    throw std::runtime_error("Unexpected end of line!");
                }
                AbstractTreeNode* res = Expr();
                if (currentType == DELIMITER || currentToken[0] == ')')
                {
                    getToken();
                    return res;
                }
                else
                {
                    delete res;
                    std::string err = "Error! \")\" expected before \"";
                    err += currentToken;
                    err += "\"!\n";
                    throw std::runtime_error(err);
                }
            }
            else
            {
                std::string err = "Error! Unexpected delimiter \"";
                err += currentToken;
                err += "\"!\n";
                throw std::runtime_error(err);
            }
        }
        break;
        default:
            throw std::runtime_error("Unexpected end of line!");
    }
}

AbstractTreeNode* Parser::Func_Call(const std::string& name)
{
    FunctionTreeNode* res = new FunctionTreeNode(name);
    AbstractTreeNode* arg = 0;
    getToken();
    if (currentType == NONE)
    {
        throw std::runtime_error("Unexpected end of line!");
    }
    if (currentType == DELIMITER && currentToken[0] == ')')
    {
        return res;
    }
    do
    {
        try
        {
            arg = Expr();
        }
        catch(std::runtime_error e)
        {
            delete res;
            throw e;
        }
        res -> addArg(arg);
        if (currentType == NONE)
        {
            delete res;
            throw std::runtime_error("Unexpected end of line!");
        }
        if (currentType == DELIMITER && currentToken[0] == ')')
        {
            getToken();
            return res;
        }
        if (currentType != DELIMITER || currentToken[0] != ',')
        {
            delete res;
            std::string err = "\",\" or \")\" expected before \"";
            err += currentToken;
            err += "\"!\n";
            throw std::runtime_error(err);
        }
        getToken();
    }
    while(true);
}
