#include "func_expcos.h"

my::FuncExpCos::FuncExpCos(){}

float my::FuncExpCos::operator()(const float & x, const float & y)const throw(std::invalid_argument)
{
    return std::exp(-x*x/2. - y*y/2.)*std::cos(2.*x*x + 2.*y*y);
}
