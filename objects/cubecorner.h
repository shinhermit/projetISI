#ifndef CUBECORNER_H
#define CUBECORNER_H

#include "triMesh.h"

namespace my{

class CubeCorner : public TriMesh
{
private:
    float _cornerSpread;
public:
    CubeCorner(float cornerSpread=0.5);
};

}

#endif // CUBECORNER_H
