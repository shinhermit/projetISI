#ifndef IPOLYGONTRIANGULATOR_H
#define IPOLYGONTRIANGULATOR_H

#include <vector>

#include "my_types.h"
#include "ipolygon.h"

/**
  * Interface for polygon triangulators
  * Using this interface allows to change the triangulation method, if new ones are given in the future.
  */
namespace my{

class IPolygonTriangulator{
public:
    virtual void process(const my::IPolygon & poly, std::vector<my::Triangle> & triangulation)=0;
};

}

#endif // IPOLYGONTRIANGULATOR_H
