#ifndef MESHREFPOLYGON_H
#define MESHREFPOLYGON_H

#include <vector>

#include "abstractpolygon.h"
#include "iMesh.h"

namespace my{

class MeshRefPolygon : public AbstractPolygon
{
private:
    const IMesh & _mesh;
    std::vector<int> _vertexRefs;

    void _preAddref(const int & ref) throw(std::invalid_argument);
    void _preIndice(const int & ref, const std::string & method)const throw(std::out_of_range);

public:
    MeshRefPolygon(const IMesh & mesh);

    void addVertex(const my::Vertex & vertex);
    void addVertex(const float & x, const float & y, const float & z);

    void addRef(const int & ref);

    void removeVertex(const int & i) throw(std::out_of_range);
    void clear();

    int size()const;
    my::Vertex vertex(const int & i)const throw(std::out_of_range);
    int vertexRef(const int & i)const throw(std::out_of_range);

    std::string toString()const;
};

}
#endif // MESHREFPOLYGON_H
