#include "func_sincos.h"

my::FuncSinCos::FuncSinCos()
    :my::Functional("FuncSinCos")
{}

float my::FuncSinCos::operator()(const float & x, const float & y)const throw(std::invalid_argument)
{
    return std::sin(x)*std::cos(y);
}
