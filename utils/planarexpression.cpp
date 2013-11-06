#include "planarexpression.h"

my::PlanarExpression::PlanarExpression(const my::Point & A, const my::Vector & u, const my::Vector & v)
{
    my::Vector u0, v0;

    u0 = glm::normalize(u);
    v0 = glm::normalize(v);

    _a = u0[1]*v0[2] - u0[2]*v0[1];
    _b = u0[2]*v0[0] - u0[0]*v0[2];
    _c = u0[0]*v0[1] - u0[1]*v0[0];
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
