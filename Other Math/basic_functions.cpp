#include "basic_functions.hpp"

double sin(const std::vector<double>& args)
{
    return sin(args.at(0));
}

double cos(const std::vector<double>& args)
{
    return cos(args.at(0));
}

double exp(const std::vector<double>& args)
{
    return exp(args.at(0));
}

double sqrt(const std::vector<double>& args)
{
    return sqrt(args.at(0));
}

double cbrt(const std::vector<double>& args)
{
    return cbrt(args.at(0));
}

double log(const std::vector<double>& args)
{
    return log(args.at(1)) / log(args.at(0));
}

double ln(const std::vector<double>& args)
{
    return log(args.at(0));
}

double if_func(const std::vector<double>& args)
{
	if (args[0]) return args[1];
	return args[2];
}

void addFunctions(Expression* expr)
{
    expr -> setFunction("sin", 1, sin);
    expr -> setFunction("cos", 1, cos);
    expr -> setFunction("exp", 1, exp);
    expr -> setFunction("sqrt", 1, sqrt);
    expr -> setFunction("cbrt", 1, cbrt);
    expr -> setFunction("log", 2, log);
    expr -> setFunction("ln", 1, ln);
	expr -> setFunction("if", 3, if_func);
}
