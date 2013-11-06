/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * The ear clipping polygon triangulation algorithme
 *
 *
 */
#ifndef EARCLIPPING_H
#define EARCLIPPING_H

#include <list>
#include <set>
#include <deque>
#include <algorithm>
#include <iostream>

#include "ipolygontriangulator.h"
#include "iMesh.h"
#include "geometry.h"

namespace my{

/**
  * Subclasses IPolygonTriangulator.
 * Implments the ear clipping polygon triangulation algorithme.
 * For more information about this algorithme, please refer to the computer sciences litterature.
 *
 */
class EarClipping : public IPolygonTriangulator
{
private:
    const my::IPolygon * _poly;
    my::Vector _orientation;
    std::vector<my::Triangle> * _triangulation;
    std::vector<int> _currentPoly;
    std::list<int> _convexVertices;
    std::list<int> _reflexVertices;
    std::deque<int> _earVertices;

    /**
      *Provides the preceeding vertex of the given one in the list of remainin unremoved vertices.
      *@param vertex indice of the following vertex
      *@return indice of the preceeding vertice
      */
    int _cyclicPrev(const int & vertex)const;

    /**
      *Provides the following vertex of the given one in the list of remainin unremoved vertices.
      *@param vertex indice of the preceeding vertex
      *@return indice of the following vertice
      */
    int _cyclicNext(const int & vertex)const;

    /**
      *Tells whether a vertex is convex or not, ie, the oriented angle between edges v-1,v and v,v+1 is less than 180°
      *@param vertex indice of the tested vertex
      *@return true if the vertex is convex, false if vertex is reflex.
      */
    bool _convexVertex(const int & vertex)const;

    /**
      *Tells if Point M is inside the triangle ABC
      *@param A first point of the triangle
      *@param B second point of the triangle
      *@param C third point of the triangle
      *@param M the tested point
      *@return true if M is inside ABC, false elsewise.
      */
    bool _insideTriangle(const my::Point & A, const my::Point & B, const my::Point & C, const my::Point & M)const;

    /**
      *Tells whether a vertex an ear vertexor not, ie, it's a convex vertex an no other vertex is inside the triangle <v-1, v, v+1>
      *@param vertex indice of the tested vertex
      *@return true if the vertex is an ear vertex, false elsewise.
      */
    bool _earVertex(const int & vertexRef)const;

    /**
      * Builds the initial lists of ear vertices, convex vertices, reflex vertices and current polygon vertices.
      */
    void _buildConvexityLists();

    /**
      * Adds to the mesh the triangle v-1, v, v+1 to the mesh, where v is the given vertex.
      * @param earVertex the earvertex that forms the triangle to be added.
      */
    void _addTriangle(const int & earVertex);

    /**
      * Checks if the immediate neighbours of a just added ear vertex have seen change in their status.
      * Precisely, the reflex vertices can turn into convex vertices or ear vertices.
      * used by _updalists.
      * @param earVertex the earvertex that has just been added.
      */
    void _checkConvexityChanges(const int & vertex);

    /**
      * Renumbers all the list after an ear vertex has been removed from the current polygon's vertices list.
      * used by _updalists.
      * @param earVertex the earvertex that has just been removed.
      */
    void _renumberLists(const int & earVertex);

    /**
      * Updates all the vertices lists after an ear vertex has been treated and removed from the current polygon.
      * uses _checkConvexityChanges and _renumberLists for that purpose.
      * @param earVertex the earvertex that has just been treated.
      */
    void _updateLists(const int & earVertex);

    void _preProcess(const my::IPolygon & poly) throw(std::invalid_argument);

    /**
      *Used to initially clean all the lists, in case the object is used several times.
      */
    void _clearLists();

    /**
      *Needed because of the compulsory interface of IPolygonTriangulator, making thus impossible to initialize properly via the constructor.
      *@param poly the polygon to be treated
      *@param triangulation a vector that will be filled with the triangles resulting from the polygon's triangulation.
      */
    void _init(const my::IPolygon & poly, std::vector<my::Triangle> & triangulation);


public:
    /**
      *Constructor
      */
    EarClipping();

    /**
      *@see my::IPolygonTriangulator::process
      */
    void process(const my::IPolygon & poly, std::vector<my::Triangle> & triangulation);

    void print_lists();
};

}

#endif // EARCLIPPING_H
