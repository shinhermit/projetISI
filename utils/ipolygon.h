/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * Interface for all polygons
 *
 *
 */
#ifndef IPOLYGON_H
#define IPOLYGON_H

#include "my_types.h"
#include "parametrics/planar.h"
#include "planarexpression.h"

namespace my{

/**
  * Abstracts the idea of polygon.
  * This project uses the MeshRefPolygon which implements IPolygon.
  * MeshRefPolygon is a polygon that holds only references of vertices of a mesh, thus represents a subset of the mesh vertices.
  */
class IPolygon
{
public:
    /**
      *Adds a vertex to the polygon
      * Add method should preserve the planar property of the polygon
      *@param vertex the vertex to be added
      *@example polygon.addVertex(my::Vertex(1.,1.,1.));
      */
    virtual void addVertex(const my::Vertex & vertex)=0;

    /**
      *Adds a vertex to the polygon
      * Add method should preserve the planar property of the polygon
      *@param x the x coordinate of the vertex to be added
      *@param y the y coordinate of the vertex to be added
      *@param z the z coordinate of the vertex to be added
      *@example polygon.addVertex(1.,1.,1.);
      */
    virtual void addVertex(const float & x, const float & y, const float & z)=0;


    /**
      *REmoves a vertex from the polygon
      *@param i indice of the vertex to be removed in the polygon
      *@example polygon.removeVertex(0);
      */
    virtual void removeVertex(const int & i) throw(std::out_of_range)=0;

    /**
      *Removes every vertex from the polygon
      */
    virtual void clear()=0;

    /**
      *Gets the number of vertices in the polygon
      */
    virtual int size()const=0;

    /**
      *Gets the vertex at the given indice
      *@param i indice of the vertex we are looking for
      */
    virtual my::Vertex vertex(const int & i)const throw(std::out_of_range)=0;

    /**
      *Gets the edge between vertex i and vertex i+1 mod nbVertex.
      * The Edge is repreentated as a vector.
      *@param i indice of the starting vertex of the edge.
      */
    virtual my::Vector edgeVector(const int & i)const throw(std::out_of_range)=0;

    /**
      * A polygon is an ordered list of vertices. Gives the vertex following the given one in that ordered list.
      *@param i indice of the preceding vertex
      */
    virtual int next(const int & i) const throw(std::out_of_range)=0;

    /**
      * A polygon is an ordered list of vertices. Gives the vertex preceding the given one in that ordered list.
      *@param i indice of the folowwing vertex
      */
    virtual int prev(const int & i) const throw(std::out_of_range)=0;

    /**
      * Provides the parametric equation of the plane where lies the polygon.
      @return an instance of my::Planar, that represents the parametric equation of the base plane of the polygon
      */
    virtual my::Planar basePlane()const=0;

    /**
      * Provides the cartesian equation of the plane where lies the polygon.
      @return an instance of my::PlanarExpression, that represents the cartesian equation of the base plane of the polygon
      */
    virtual my::PlanarExpression basePlaneExpression()const=0;

    /**
      * Provides the orientation vector of the polygon.
      * Orientation vector is a normal vector computed by successive vectors cross products.
      * The magnitude of the vector is the area of the polygon.
      *@return the polygon's orientation vector
      */
    virtual my::Vector orientationVector()const=0;

    /**
      *Provides the orientation of the polygon, as my::CLOCKWISE or my::COUNTER_CLOCKWISE, in relation to a sighting vector.
      *@param sightingVector the sighting vector. Note that sighting vector goes from the object to the observer (points to the sighting position).
      *@return the orientation of the polygon
     */
    virtual my::Orientation orientation(const my::Vector & sightingVector)const=0;

    /**
      *Provides the signed area of the polygon, in relation to the sighting vector.
      * This allows to know the orientation of the polygon. The area of the polygon is given by the absolute value of the signed area.
      *@param sightingVector the sighting vector.  Note that sighting vector goes from the object to the observer (points to the sighting position).
      *@return Value of the signed area of the polygon
      */
    virtual float signedArea(const my::Vector & sightingVector)const=0;

    /**
      *Provides the area of the polygon.
      * Simply the absolute value of the signed area.
      *@return the area of the polygon
      */
    virtual float area()const=0;

    /**
      *Provides the circumference of the polygon.
      *@return the circumference of the polygon
      */
    virtual float circumference()const=0;

    /**
      *Provides a string representation of the polygon.
      *@return string representation of the polygon
      */
    virtual std::string toString()const=0;
};

}
#endif // IPOLYGON_H
