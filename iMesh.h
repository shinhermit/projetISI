/**
 * @author Bruno Jobard
 * @date   Oct 2012
 *
 *  Defines 3D triangular mesh
 *
 *
 */
#ifndef  _IMESH_H_
#define  _IMESH_H_

#include <stdexcept>

#include "my_types.h"

using namespace std;
/** 
 * Interface for Mesh Objects
 *
 */
namespace my{

class IMesh
{
public:
    /**
   * adds a vertex to the mesh
   * @param v the vertex to be added
   */
    virtual void addVertex(my::Vertex v)=0;

    /**
   * adds a vertex to the mesh
   * @param x the x coordinate of the vertex to be added
   * @param y the y coordinate of the vertex to be added
   * @param z the z coordinate of the vertex to be added
   */
    virtual void addVertex(double x, double y, double z)=0;


    /**
   * adds a triangle to the mesh
   * @param t the triangle to be added
   */
    virtual void addTriangle(my::Triangle t)=0;

    /**
   * adds a triangle to the mesh
   * @param v1 first vertex of the triangle
   * @param v2 second vertex of the triangle
   * @param v3 third vertex of the triangle
   */
    virtual void addTriangle(int v1, int v2, int v3)=0;

    /**
   * updates the vertices of a triangle in the mesh
   * @param t indice of the triangle to be updated
   * @param up up to date triangle
   */
    virtual void updateTriangle(const int & t, const my::Triangle & up) throw(std::out_of_range)=0;

    /**
   * updates the vertices of a triangle in the mesh
   * @param t indice of the triangle to be updated
   * @param v1 first vertex of the triangle
   * @param v2 second vertex of the triangle
   * @param v3 third vertex of the triangle
   */
    virtual void updateTriangle(const int & t, int v1, int v2, int v3) throw(std::out_of_range)=0;

    /**
   * Set the color of the vertex indiced by the given argument
   * @param vertex indice of the vertex that is to be colored
   * @param col RGBA color of the vertice
   * @example setColor(0, my::Color(0.3,0.4,0.1,1);
   */
    virtual void setVertexColor(const int & vertex, const my::Color & col)=0;

    /**
   * Set the color of the vertex indiced by the given argument
   * @param vertex indice of the vertex that is to be colored
   * @param col RGBA color of the vertice
   * @example setColor(0, my::Color(0.3,0.4,0.1,1);
   */
    virtual void setVertexColor(const int & vertex, const float & R, const float & G, const float & B, const float & A)=0;

    /**
   * Set the color of the vertices of the tirnagle indiced by the given argument
   * @param triangle indice of the triangle that is to be colored
   * @param col RGBA color of the vertice
   * @example setColor(0, my::Color(0.3,0.4,0.1,1);
   */
    virtual void setTriangleColor(const int & triangle, const my::Color & col)=0;
    /**
   * Set the color of the vertices of the tirnagle indiced by the given argument
   * @param triangle indice of the triangle that is to be colored
   * @param col RGBA color of the vertice
   * @example setColor(0, my::Color(0.3,0.4,0.1,1);
   */
    virtual void setTriangleColor(const int & triangle, const float & R, const float & G, const float & B, const float & A)=0;

    /**
   * adds a triangle normal to the mesh
   * @param n the normal to be added
   */
    virtual void addNormalT(my::Normal n)=0;

    /**
   * adds a vertex normal to the mesh
   * @param n the normal to be added
   */
    virtual void addNormalV(my::Normal n)=0;

    /**
   * merges two vertices into one.
   * Collapses the vertice indiced by slave on the vertice indiced by master, meaning that the resulting vertice is geometrically equivalent to master.
   * @param slave indice of the vertex that will be collapsed on the other
   * @param master indice of the vertex that will remain after caollapsing
   */
    virtual void collapseVertices(const int & slave, const int & master, bool computeNormals=false)=0;


    /**
   * merges a number of vertice by pair.
   * First vertice of range slave is collapsed on first vertice of range master, second slave on second master, and so on.
   * Primary use is to make 2 separate surfaces into one.
   * length of range master must be greater than or equal to the length of range slave.
   * @param slaves range of indices of the vertices that will be collapsed on the others
   * @param masters range of indices of the vertices that will remain after collapsing.
   */
    virtual void sew(const my::Range & slaves, const my::Range & masters)=0;

    /**
   * flips the orientation of all the triangles in the mesh.
   */
    virtual void flipTriangles()=0;

    /**
   * gets the number of vertices
   * @return number of vertices in the mesh
   */
    virtual int sizeV()const=0;

    /**
   * gets the number of triangles
   * @return number of triangles in the mesh
   */
    virtual int sizeT()const=0;

    /**
   * gets a vertex
   * @param index the index of the vertex
   */
    virtual my::Vertex getVertex(const int & index)const=0;

    /**
   * gets a vertex indice relatively to a triangle
   * @param triangle index of the triangle
   * @param vertexInTriangle index of vertex in the triangle (0, 1 or 2)
   */
    virtual int getVertexIndice(const int & triangle, const int & vertexInTriangle)const=0;


    /**
   * updates the bouding box of the object
   */
    virtual void computeBoundingBox()=0;

    /**
   * computes the triangles normals of the 3D mesh
   */
    virtual void computeNormalsT()=0;

    /**
   * computes the vertices normals of the 3D mesh.
   *
   * it requires triangles normals to be computed first
   * @see computeNormalsT
   * @param threshold the angles beyond which two faces are considered to have a sharp edge
   */
    virtual void computeNormalsV(float threshold=70.)=0;

    /**
   * scales and centers the objects so it fits in the [-1:1]^3
   * @return the scaling factor
   */
    virtual double normalize()=0;
};

}

#endif
