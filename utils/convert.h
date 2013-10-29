#ifndef CONVERT_H
#define CONVERT_H

#include <sstream>

namespace my{

/**
 * Utility class for numeric values conversion.
 *
 * Precision errors introduced by cast from float to int, as in redefinitions of method Trimesh::_indiceOfVertexAt, causes triangles insertion errors.
 * This generic class uses standard sstream to solve this.
 */
template<typename T, typename U>
class Convert
{
public:
    Convert();
    U operator()(T t);
};

}

#include "convert.cpp"

#endif // CONVERT_H
