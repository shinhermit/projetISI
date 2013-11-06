/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * Interface for polygon triangulators
 *
 *
 */
#ifndef IPOLYGONTRIANGULATOR_H
#define IPOLYGONTRIANGULATOR_H

#include <vector>

#include "my_types.h"
#include "ipolygon.h"

namespace my{

/**
  * Interface for polygon triangulators
  * Using this interface allows to change the triangulation method, if new ones are given in the future.
  */
class IPolygonTriangulator{
public:
    /**
      *Triangulates the given polygon.
      *@param poly the polygon to be triangulated
      *@param triangulation a vector that will be filled with the result of the triangulation.
      */
    virtual void process(const my::IPolygon & poly, std::vector<my::Triangle> & triangulation)=0;
};

}

#endif // IPOLYGONTRIANGULATOR_H
