/**
 * @author Bruno Jobard
 * @date   Oct 2012
 *
 *  Defines 3D triangular mesh
 *
 *
 */
#ifndef  _TRIMESH_H_
#define  _TRIMESH_H_

#include <QDebug>

#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <assert.h>

#include "my_object3d.h"
#include "my_types.h"
#include "parametrics/parametric.h"
#include "functionals/functional.h"
#include "utils/convert.h"
#include "utils/constant.h"



using namespace std;
/** 
 * Simple Triangular Mesh Object
 *
 */
class TriMesh : public Object3D {

protected:
  std::vector<my::Vertex>   _vertices;
  std::vector<my::Triangle> _triangles;
  std::vector<my::Normal>   _normalsT;
  std::vector<my::Normal>   _normalsV;

public:
  TriMesh(const std::string & name="Trimesh");
  virtual ~TriMesh(){}

  /**
   * draws the 3D object
   * @param flipnormals specifies if normals are flipped (default is false, the triangles are counter clock-wise)
   */
  virtual void draw(bool flipnormals=false);

  /**
   * draws the normals as line segments
   * @param flipnormals specifies if normals are flipped (default is false, the triangles are counter clock-wise)
   */
  virtual void drawNormals(bool flipnormals=false);

  /**
   * draws the vertices as points
   */
  virtual void drawVertices();

  /**
   * adds a vertex to the mesh
   * @param v the vertex to be added
   */
  void addVertex(my::Vertex v);

  /**
   * adds a vertex to the mesh
   * @param x the x coordinate of the vertex to be added
   * @param y the y coordinate of the vertex to be added
   * @param z the z coordinate of the vertex to be added
   */
  void addVertex(double x, double y, double z);


  /**
   * adds a triangle to the mesh
   * @param t the triangle to be added
   */
  void addTriangle(my::Triangle t);

  /**
   * adds a triangle to the mesh
   * @param v1 first vertex of the triangle
   * @param v2 second vertex of the triangle
   * @param v3 third vertex of the triangle
   */
  void addTriangle(int v1, int v2, int v3);


  /**
   * adds a triangle normal to the mesh
   * @param n the normal to be added
   */
  void addNormalT(my::Normal n);

  /**
   * adds a vertex normal to the mesh
   * @param n the normal to be added
   */
  void addNormalV(my::Normal n);

  /**
   * includes the geometry (vertices and triangle) of another TriMesh in the current mesh
   * @param mesh the mesh we want to include
   */
  void includeMesh(const TriMesh & mesh);

  void _preCollapseVertices(const int & slave, const int & master) throw(std::invalid_argument);

  /**
   * merges two vertices into one.
   * Collapses the vertice indiced by slave on the vertice indiced by master, meaning that the resulting vertice is geometrically equivalent to master.
   * @param slave indice of the vertex that will be collapsed on the other
   * @param master indice of the vertex that will remain after caollapsing
   */
  void collapseVertices(const int & slave, const int & master, bool computeNormals=false);


  void _preSew(const my::Range & slaves, const my::Range & masters) throw(std::invalid_argument);

  /**
   * merges a number of vertice by pair.
   * First vertice of range slave is collapsed on first vertice of range master, second slave on second master, and so on.
   * Primary use is to make 2 separate surfaces into one.
   * length of range master must be greater than or equal to the length of range slave.
   * @param slaves range of indices of the vertices that will be collapsed on the others
   * @param masters range of indices of the vertices that will remain after collapsing.
   */
  void sew(const my::Range & slaves, const my::Range & masters);

  /**
   * flips the orientation of all the triangles in the mesh.
   */
  void flipTriangles();

  /**
   * gets the number of vertices
   * @return number of vertices in the mesh
   */
  int sizeV()const;

  /**
   * gets the number of triangles
   * @return number of triangles in the mesh
   */
  int sizeT()const;

  /**
   * gets a vertex
   * @param index the index of the vertex
   */
  my::Vertex getVertex(int index);

  virtual std::string toString();
  virtual void toOStream(std::ostream& out=std::cout) const;

  /**
   * updates the bouding box of the object
   */
  void computeBoundingBox();

  /**
   * computes the triangles normals of the 3D mesh
   */
  void computeNormalsT();

  /**
   * computes the vertices normals of the 3D mesh.
   *
   * it requires triangles normals to be computed first
   * @see computeNormalsT
   * @param threshold the angles beyond which two faces are considered to have a sharp edge
   */
  void computeNormalsV(float threshold=70.);

  /**
   * scales and centers the objects so it fits in the [-1:1]^3
   * @return the scaling factor
   */
  double normalize();


};


#endif
