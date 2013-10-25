#include "planar.h"

my::Planar::Planar(const my::Point & A, const my::Vector & u, const my::Vector & v)
    :_A(A),
      _u(u),
      _v(v)
{}

my::Point my::Planar::operator ()(const float & s, const float & t) throw(std::invalid_argument)
{
    return my::Point(_A[0] + _u[0]*s + _v[0]*t,
                     _A[1] + _u[1]*s + _v[1]*t,
                     _A[2] + _u[2]*s + _v[2]*t);
}
