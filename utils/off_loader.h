/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * Load a mesh from a file.
 *
 */
#ifndef OFF_LOADER_H
#define OFF_LOADER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>

#include <glm/gtx/vector_angle.hpp>

#include "iMesh.h"
#include "ipolygontriangulator.h"
#include "geometry.h"
#include "meshrefpolygon.h"
#include "earclipping.h"

namespace my{

/**
  * OffLoader is not a mesh, it's a tool to load meshes.
  * Therefore, it should'nt inherit TriMesh, but should be usable as a component.
  */
class OffLoader
{
private:
    my::IMesh & _mesh;
    std::string _filename;
    std::fstream _file;
    unsigned int _lineNum;
    my::IPolygonTriangulator * _triangulator;
    int _nbTreatedFaces; //debug tool
    int _nbTriangulatedFaces; //debug tool

    /**
      * Treat Windows-like newline (\r\n)
      */
    std::basic_istream<char> & _getline(std::fstream & file, std::string & line);

    /**
      * Get only data line (skips comments and blank lines)
      */
    std::basic_istream<char> & _getDataLine(std::fstream & file, std::string & line);

    /**
      *Read the line of the file that indicates the sizes in the geometry
      *@param vertex_count will contain the number of vertices specified in the file
      *@param face_count will contain the number of polygons specified in the file
      *@param edge_count will contain the number of edges specified in the file (not used)
      */
    void _getSizes(int & vertex_count, int & face_count, int & edge_count) throw(std::runtime_error);

    /**
      * Read colors information (vertices or polygons)
      *@param iss the string stream associated to the data line read from the file
      *@param R red component of the color
      *@param G green component of the color
      *@param B bleu component of the color
      *@param A alpha channel of the color
      */
    bool _getColor(std::istringstream & iss, float & R, float & G, float & B, float & A);

    void _postGetElement(const int & actual, const int & specified, const std::string & elementName, const std::string & methodName) throw(std::runtime_error);
    void _exceptInvalidDataFormat(const std::string & line, const std::string & element, const std::string & methodName, const std::string & moreInfo) throw(std::runtime_error);
    void _exceptInvalidValue(const std::string & methodName, const std::string & element, const std::string & valueType, const float & value, const float & rangeMin, const float & rangeMax, const std::string & moreInfo) throw(std::out_of_range);

    /**
      *Extracts the vertices from the file
      *@param vertex_count the number of vertices specified in the file
      */
    void _getVertices(const int & vertex_count) throw(std::runtime_error);

    /**
      *Extracts the polygons from the file
      *@param face_count the number of polygons specified in the file
      */
    void _getPolygons(const int & face_count) throw(std::runtime_error, std::out_of_range);

    /**
      *Perfoms _getVertices and _getPolygons
      */
    void _getMesh() throw(std::runtime_error, std::range_error);

    /**
      *Responsible for inserting triangles in the mesh. Triangulates first any polygon with more than 3 vertices.
      *@param polygon the polygon whose triangles must be inserted in the mesh
      *@param col RGBA color of the triangle that is to be added.
      */
    void _addTriangles(my::MeshRefPolygon & polygon, const my::Color * col=0);

public:
    ~OffLoader();

    /**
      *Constructor
      *@param receptacle the mesh that will receive the geometry from the file
      *@param filename the file to be loaded
      *@param triangulator a subclass of IPolygonTriangulator, that will handle triangulation of polygons with more than 3 vertices.
      */
    OffLoader(my::IMesh & receptacle, const std::string & filename, my::IPolygonTriangulator * triangulator=0) throw(std::invalid_argument);
    void load();
};

}

#endif // OFF_LOADER_H
