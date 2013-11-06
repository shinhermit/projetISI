/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * Holds useful geometrical functions
 *
 *
 */
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "planarexpression.h"
#include "constant.h"

namespace my{

/**
  *Defines useful missing function for some geometrical calculations.
 *
 */
class Geometry
{
public:
    /**
      *glm::angle is unable to give an oriented angle, which can be useful to distinguish convex angles from concaves.
      *Using glmangle while ignoring this results in algorithmes that only works in some particular cases.
      * This function provides oriented angles by space partition. The partition is done by a plane.
      * @param u the first vector that formes the angle
      * @param v the second vector that formes the angle
      * @return oriented (signed) angle between u and v, in range [-180,180]
      */
    static float angle(const my::Vector & u, const my::Vector & v);

    /**
      * Based on my::Geometry::angle, this function provides angle in range [0,360]
      * @param u the first vector that formes the angle
      * @param v the second vector that formes the angle
      * @return oriented (signed) angle between u and v, in range [0,360]
      */
    static float angle360(const my::Vector & u, const my::Vector & v);

    /**
      * Converts an angle from degree to radian
      * @param degAngle an angle in degree
      * @return the angle in radian
      */
    static float degreeToRadian(const float & degAngle);

    /**
      * Converts an angle from radian to degree
      * @param degAngle an angle in radian
      * @return the angle in degree
      */
    static float radianToDegree(const float & radAngle);
};

}

#endif // GEOMETRY_H
