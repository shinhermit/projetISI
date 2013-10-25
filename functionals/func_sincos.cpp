#include "func_sincos.h"

my::FuncSinCos::FuncSinCos(){}

float my::FuncSinCos::operator()(const float & x, const float & y)const throw(std::invalid_argument)
{
//    return std::sin(-x*x/2. - y*y/2.)*std::cos(2.*x*x + 2.*y*y);
    return std::sin(x)*std::cos(y);
}
