/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * An octahedreon
 *
 *
 */
#ifndef OCTAEDRON_H
#define OCTAEDRON_H

#include "triMesh.h"

namespace my{

class Octahedron : public TriMesh
{
public:
    /**
      *Constructor
      *@param radius radius of circumscribed circle
      */
    Octahedron(const float & radius=1.);
};

}

#endif // OCTAEDRON_H
