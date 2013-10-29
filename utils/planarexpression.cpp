#include "planarexpression.h"

my::PlanarExpression::PlanarExpression(const my::Point & A, const my::Vector & u, const my::Vector & v)
{
    _a = u[1]*v[2] - u[2]*v[1];
    _b = u[2]*v[0] - u[0]*v[2];
    _c = u[0]*v[1] - u[1]*v[0];
    _d = -_a*A[0] - _b*A[1] - _c*A[2];
}

float my::PlanarExpression::operator ()(const float & x, const float & y, const float & z) const
{
    return _a*x + _b*y + _c*z + _d;
}

float my::PlanarExpression::operator ()(const my::Point & P) const
{
    return operator()(P[0], P[1], P[2]);
}
