/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * An implementation of my::IPolygon
 *
 *
 */
#ifndef MESHREFPOLYGON_H
#define MESHREFPOLYGON_H

#include <vector>

#include "abstractpolygon.h"
#include "iMesh.h"

namespace my{

/**
  * Implements my::AbstractPolygon, that partially implments my::IPolygon.
  * MeshRefPolygon is a polygon that holds only references of vertices of a mesh, thus represents a subset of the mesh vertices.
  */
class MeshRefPolygon : public AbstractPolygon
{
private:
    const IMesh & _mesh;
    std::vector<int> _vertexRefs;

    void _preAddref(const int & ref) throw(std::invalid_argument);
    void _preIndice(const int & ref, const std::string & method)const throw(std::out_of_range);

public:
    MeshRefPolygon(const IMesh & mesh);

    /**
      *@see my::IPolygon::addVertex
      */
    void addVertex(const my::Vertex & vertex);

    /**
      *@see my::IPolygon::addVertex
      */
    void addVertex(const float & x, const float & y, const float & z);

    /**
      * Adds a vertex reference in the MeshRefPolygon.
      * A reference is the indice of a vertex in it's original mesh.
      */
    void addRef(const int & ref);

    /**
      *@see my::IPolygon::removeVertex
      */
    void removeVertex(const int & i) throw(std::out_of_range);

    /**
      *@see my::IPolygon::clear
      */
    void clear();


    /**
      *@see my::IPolygon::size
      */
    int size()const;

    /**
      *@see my::IPolygon::vertex
      */
    my::Vertex vertex(const int & i)const throw(std::out_of_range);

    /**
      *@see my::IPolygon::vertexRef
      */
    int vertexRef(const int & i)const throw(std::out_of_range);

    /**
      *@see my::IPolygon::toString
      */
    std::string toString()const;
};

}
#endif // MESHREFPOLYGON_H
