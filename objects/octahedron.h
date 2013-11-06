#ifndef OCTAEDRON_H
#define OCTAEDRON_H

#include "triMesh.h"

namespace my{

class Octahedron : public TriMesh
{
public:
    Octahedron(const float & radius=1.);
};

}

#endif // OCTAEDRON_H
