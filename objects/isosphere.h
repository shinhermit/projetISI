/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * An octahedreon based sphere
 *
 *
 */
#ifndef ISOSPHERE_H
#define ISOSPHERE_H

#include "octahedron.h"

namespace my{

/**
  * The principle is to beging with a regular polyhedron, and than devide regularly the faces of the polyhedron.
  * Each time a vertex is inserted, it's pushed to the surface of the sphere.
  * The primary goal is th obtaina subdivision that best matches the purpose of smooth lighting.
 *
 */

class IsoSphere : public TriMesh
{
private:
    float _radius;
    int _nbIter;
    std::map<my::Edge,int> _middles;

    /**
      * If the middle point of segment AB has not been computed yet, computes that middle and keeps track of it.
      * If the middle has already been computed, just return this middle vertex.
      * @param iA indice of a vertex that we name A
      * @param iB indice of another vertex, that we name B
      * @return the middle point of segment AB
      */
    int _getMiddle(const int & iA, const int & iB);


    /**
      *Performs the subdivision for every triangle in the mesh into four smaller triangles.
      */
    void _subdivide();

public:
    /**
      *Constructor
      *@param radius radius of circumscribed circle
      *@param number of ieteration of the subdivision.
      */
    IsoSphere(const float & radius=1., const int & nbIter=3);
};

}

#endif // ISOSPHERE_H
