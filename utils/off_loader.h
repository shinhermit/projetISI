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

/**
  * OffLoader is not a mesh, it's a tool to load meshes.
  * Therefore, it should'nt inherit TriMesh, but should be usable as a component.
  */
namespace my{

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

    void _getSizes(int & vertex_count, int & face_count, int & edge_count) throw(std::runtime_error);
    bool _getColor(std::istringstream & iss, float & R, float & G, float & B, float & A);
    void _postGetElement(const int & actual, const int & specified, const std::string & elementName, const std::string & methodName) throw(std::runtime_error);
    void _exceptInvalidDataFormat(const std::string & line, const std::string & element, const std::string & methodName, const std::string & moreInfo) throw(std::runtime_error);
    void _exceptInvalidValue(const std::string & methodName, const std::string & element, const std::string & valueType, const float & value, const float & rangeMin, const float & rangeMax, const std::string & moreInfo) throw(std::out_of_range);
    void _getVertices(const int & vertex_count) throw(std::runtime_error);
    void _getPolygons(const int & face_count) throw(std::runtime_error, std::out_of_range);
    void _getMesh() throw(std::runtime_error, std::range_error);
    void _addTriangles(my::MeshRefPolygon & polygon, const my::Color * col=0);
public:
    ~OffLoader();
    OffLoader(my::IMesh & receptacle, const std::string & filename, my::IPolygonTriangulator * triangulator=0) throw(std::invalid_argument);
    void load();
};

}

#endif // OFF_LOADER_H
