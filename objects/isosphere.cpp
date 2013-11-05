#include "isosphere.h"

int IsoSphere::_getMiddle(const int & iA, const int & iB)
{
    std::map<my::Edge, int>::iterator it;
    my::Vertex A,B,M;
    int iM;

    it = _middles.find(my::Edge(iA,iB));
    if(it == _middles.end())
        it = _middles.find(my::Edge(iB,iA));

    if(it == _middles.end()){
        A = getVertex(iA);
        B = getVertex(iB);

        M = A+B; M /= 2;
        M = _radius * glm::normalize(M); //push to surface

        addVertex(M);
        iM = sizeV()-1;
        _middles[my::Edge(iA,iB)] = iM;
    }
    else
        iM = it->second;

    return iM;
}

void IsoSphere::_subdivide()
{
    int A, B, C, D, E, F;
    int nbTriangles = sizeT();

    for(int i=0; i < nbTriangles; ++i){
        A = getVertexIndice(i,0);
        B = getVertexIndice(i,1);
        C = getVertexIndice(i,2);

        //update and add triangles
        D = _getMiddle(A,B);
        E = _getMiddle(B,C);
        F = _getMiddle(C,A);

        updateTriangle(i, A, D, F);
        addTriangle(B, E, D);
        addTriangle(D, E, F);
        addTriangle(C, F, E);
    }
}

my::IsoSphere::IsoSphere(const float & radius, const int & nbIter)
    :TriMesh("IsoSphere"),
      _radius(radius),
      _nbIter(nbIter)
{
    includeMesh(my::Octahedron(radius));

    for(int i=0; i < nbIter; ++i)
        _subdivide();

    computeNormalsT();
    computeNormalsV();
}
