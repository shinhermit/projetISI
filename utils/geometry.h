#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "planarexpression.h"
#include "constant.h"

namespace my{

class Geometry
{
public:
    static float angle(const my::Vector & u, const my::Vector & v);
    static float angle360(const my::Vector & u, const my::Vector & v);
    static float degreeToRadian(const float & degAngle);
    static float radianToDegree(const float & radAngle);
};

}

#endif // GEOMETRY_H
