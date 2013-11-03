#include "geometry.h"

float my::Geometry::angle(const my::Vector & u, const my::Vector & v)
{
    my::Vector u0, v0;
    short sign;

    u0 = glm::normalize(u);
    v0 = glm::normalize(v);

    my::PlanarExpression equation(my::Point(0,0,0), u0, glm::cross(u0,v0));

    sign = ( equation(v0[0],v0[1],v0[2]) >= 0 ) ? -1 : 1;

    return sign * glm::angle(u0,v0);
}

float my::Geometry::angle360(const my::Vector & u, const my::Vector & v)
{
    float angle;

    angle = my::Geometry::angle(u,v);

    if(angle < 0)
        angle += 360;

    return angle;
}

float my::Geometry::degreeToRadian(const float & degAngle)
{
    return degAngle*my::Constant::pi / 180.;
}

float my::Geometry::radianToDegree(const float & radAngle)
{
    return radAngle*180. / my::Constant::pi;
}