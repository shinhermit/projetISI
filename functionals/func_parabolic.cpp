#include "func_parabolic.h"

my::FuncParabolic::FuncParabolic()
    :my::Functional("FuncParabolic")
{
}

float my::FuncParabolic::operator()(const float & x, const float & y)const throw(std::invalid_argument)
{
    return -2*x*x - 2*y*y;
}
