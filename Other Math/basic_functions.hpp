#ifndef BASIC_FUNCTIONS_HPP
#define BASIC_FUNCTIONS_HPP

#include <cmath>
#include <vector>
#include <expression.hpp>
using namespace OperationTree;

double sin(const std::vector<double>& args);
double cos(const std::vector<double>& args);
double exp(const std::vector<double>& args);
double sqrt(const std::vector<double>& args);
double cbrt(const std::vector<double>& args);
double log(const std::vector<double>& args);
double ln(const std::vector<double>& args);
double if_func(const std::vector<double>& args);

void addFunctions(Expression* expr);

#endif // BASIC_FUNCTIONS_HPP
