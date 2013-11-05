#ifndef ISOSPHERE_H
#define ISOSPHERE_H

#include "octahedron.h"

namespace my{

class IsoSphere : public TriMesh
{
private:
    float _radius;
    int _nbIter;
    std::map<my::Edge,int> _middles;

    int _getMiddle(const int & iA, const int & iB);
    void _subdivide();
public:
    IsoSphere(const float & radius=1., const int & nbIter=3);
};

}

#endif // ISOSPHERE_H
