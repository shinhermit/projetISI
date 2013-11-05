#include "cubecorner.h"

using namespace my;

CubeCorner::CubeCorner(float cornerSpread)
    :TriMesh("CubeCorner")
{
    if(0. < cornerSpread < 1.)
        _cornerSpread = 2. * cornerSpread;
    else
        _cornerSpread = 1.; //2 * 0.5

    // vertex coordinates
    static const GLfloat vertex[10][3] = {
        {1-_cornerSpread,1,1}, {1,1-_cornerSpread,1}, {1,1,1-_cornerSpread}, //the corner
        {-1,1,1}, {-1,-1,1}, {1,-1,1},
        {1,1,-1}, {1,-1,-1}, {-1,-1,-1}, {-1,1,-1}
    };

    // triangles vertex indices
    static const GLint triangle[16][3] = {
      {0,1,2},  // corner
      {3,4,0},{0,4,1},{1,4,5},  // front
      {9,6,8},{6,7,8},  // back
      {4,8,5},{5,8,7},  // bottom
      {3,0,9},{0,2,9},{2,6,9},  // top
      {3,8,4},{3,9,8},  // left
      {1,5,7},{1,7,2},{2,7,6}   // right
    };

    // Fill vertices vector
    for (int i=0; i<10 ; ++i)
      this->addVertex(vertex[i][0], vertex[i][1], vertex[i][2]);

    // Fill triangles vector
    for (int i=0; i<16; ++i)
      this->addTriangle(triangle[i][0], triangle[i][1], triangle[i][2]);

    computeNormalsT();
    computeNormalsV();

}
