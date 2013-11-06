#include "octahedron.h"

my::Octahedron::Octahedron(const float & adius)
    :TriMesh("Octahedron")
{
    /****** vertices ******/
    //top an bottom vertices
    addVertex(0, radius, 0);
    addVertex(0, -radius, 0);

    //equatorial vertices
    addVertex(radius, 0, 0);
    addVertex(0, 0, -radius);
    addVertex(-radius, 0, -0);
    addVertex(0, 0, radius);

    /****** triangles ******/
    //top pyramid
    addTriangle(0, 5, 2); //front
    addTriangle(0, 2, 3); //right
    addTriangle(0, 3, 4); //back
    addTriangle(0, 4, 5); //left

    //bottom pyramid
    addTriangle(1, 2, 5); //front
    addTriangle(1, 3, 2); //right
    addTriangle(1, 4, 3); //back
    addTriangle(1, 5, 4); //left

    computeNormalsT();
    computeNormalsV();
}
