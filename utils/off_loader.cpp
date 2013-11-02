#include "off_loader.h"

void my::OffLoader::_addTriangles(my::MeshRefPolygon & poly)
{
    std::ostringstream oss;
    std::vector<my::Triangle> triangulation;
    std::vector<my::Triangle>::iterator it;

    if(poly.size() == 3){
        _mesh.addTriangle(poly.vertexRef(0), poly.vertexRef(1), poly.vertexRef(2));
    }

    else if(poly.size() > 3){
        _triangulator->process(poly, triangulation);

        for(it=triangulation.begin(); it != triangulation.end(); ++it){
            _mesh.addTriangle(poly.vertexRef(it->at(0)), poly.vertexRef(it->at(1)), poly.vertexRef(it->at(2)));
        }
        ++_nbTriangulatedFaces;
    }

    else{
        oss << "OffLoader::_addTriangles: polygon with less than 3 vertices encountered" << std::endl
            << "\t in file " << _filename << std::endl
            << "\t at line " << _lineNum << std::endl
            << "\t polygon size is " << poly.size() << std::endl;
        throw std::runtime_error(oss.str());
    }

    ++_nbTreatedFaces;
}

std::basic_istream<char> & my::OffLoader::_getline(std::fstream & file, std::string & line)
{
    std::basic_istream<char> & got = std::getline(file, line);

    if(got){
        ++_lineNum;
        if(line.size() > 0){
            int last = line.size()-1;
            if(line[last] == '\r')
                line.erase(line.begin()+last);
        }
    }

    return got;
}

std::basic_istream<char> & my::OffLoader::_getDataLine(std::fstream & file, std::string & line)
{
    //Comments and blank lines
    bool got = _getline(file, line);
    while(got && (line=="" || line[0]=='#'))
        got = _getline(file, line);

    return file;
}

void my::OffLoader::_getSizes(fstream & file, int & vertex_count, int & face_count, int &edge_count) throw(std::runtime_error)
{
    std::ostringstream oss;
    std::istringstream iss;
    std::string line;
    bool invalid;

    _getDataLine(file, line);
    iss.str(line);

    invalid = false;
    if(iss >> vertex_count)
        if(iss >> face_count)
            if(iss >> edge_count);
            else invalid = true;
        else invalid = true;
    else invalid = true;

    if(invalid)
    {
        oss << "OffLoader::_getSizes: sizes data line is invalid" << std::endl
            << "\t in file " << _filename << std::endl
            << "\t at line " << _lineNum << std::endl;
        throw std::runtime_error(oss.str());
    }

}

bool my::OffLoader::_getColor(std::istringstream & iss, float & R, float & G, float & B, float & A)
{
    bool colored;

    colored = false;
    if(iss >> R)
        if(iss >> G)
            if(iss >> B)
                colored = true;
    if(! (iss >> A))
        A = 1.;

    return colored;
}

void my::OffLoader::_postGetElement(const int & actual, const int & specified, const std::string & elementName, const std::string & methodName) throw(std::runtime_error)
{
    std::ostringstream oss;

    if(actual != specified){
        oss << "OffLoader::_postGetElement (for " << methodName << "): number of " << elementName << " is different from specified number" << std::endl
            << "\t in file " << _filename << std::endl
            << "\t at line " << _lineNum << std::endl
            << "\t specified number is " << specified << std::endl
            << "\t actual number is " << actual << std::endl;
        throw std::runtime_error(oss.str());
    }
}

void my::OffLoader::_getVertices(fstream & file, const int & vertex_count) throw(std::runtime_error)
{
    std::ostringstream oss;
    std::string line;
    float x,y,z;
    float R,G,B,A;
    bool invalid;
    int i;

    i = 0;
    while(i < vertex_count && _getDataLine(file, line)){
        std::istringstream iss(line);
        //coordinates
        invalid = false;
        if(iss >> x)
            if(iss >> y)
                if(iss >> z);
                else invalid = true;
            else invalid = true;
        else invalid = true;

        if(invalid){
            oss << "OffLoader::_getMesh: invalid vertex informations" << std::endl
                << "\t in file " << _filename << std::endl
                << "\t at line " << _lineNum << std::endl
                << "\t last read line: [[" << line << "]]" << std::endl;
            throw std::runtime_error(oss.str());
        }

        _mesh.addVertex(x,y,z);

        if(_getColor(iss, R,G,G,A))
            _mesh.setVertexColor(_mesh.sizeV()-1, R,G,B,A);

        ++i;
    }

    _postGetElement(i, vertex_count, "vertices", "_getVertices");
}

void my::OffLoader::_getPolygons(fstream & file, const int & face_count) throw(std::runtime_error, std::out_of_range)
{
    std::ostringstream oss;
    std::string line;
    int polygonSize;
    float R,G,B,A;
    int i, j;
    int vertex;
    my::MeshRefPolygon poly(_mesh);

    i=0;
    while(i < face_count && _getDataLine(file, line)){
        std::istringstream iss(line);

        if(! (iss >> polygonSize) ){
            oss << "OffLoader::_getMesh: invalid face specification encountered. Number of vertices invalid" << std::endl
                << "\t in file " << _filename << std::endl
                << "\t at line " << _lineNum << std::endl;
            throw std::runtime_error(oss.str());
        }

        j = 0;
        poly.clear();
        while( (iss >> vertex) && (j < polygonSize) ){
            if(! (0 <= vertex && vertex < _mesh.sizeV()) ){
                oss << "OffLoader::_getMesh: encounter polygon with vertex indice out or range" << std::endl
                    << "\t range is [0," << _mesh.sizeV() << "]" << std::endl
                    << "\t encountered indice is " << vertex << std::endl
                    << "\t in file " << _filename << std::endl
                    << "\t at line " << _lineNum << std::endl;
                throw std::out_of_range(oss.str());
            }

            poly.addRef(vertex);
            ++j;
        }

        _postGetElement(j, polygonSize, "vertices in polygon", "_getPolygons");

        _addTriangles(poly);

        if(_getColor(iss, R,G,B,A)){
            for(int i=0; i < poly.size(); ++i){
                _mesh.setVertexColor(poly.vertexRef(i), R,G,B,A);
            }
        }

        ++i;
    }

    _postGetElement(i, face_count, "polygons", "_getPolygons");
}

void my::OffLoader::_getMesh(std::fstream & file) throw(std::runtime_error, std::range_error)
{
    int vertex_count, face_count, edge_count;

    _getSizes(file, vertex_count, face_count, edge_count);

    _getVertices(file, vertex_count);

    _getPolygons(file, face_count);
}

my::OffLoader::OffLoader(my::IMesh & receptacle, const std::string & filename, my::IPolygonTriangulator * triangulator) throw(std::invalid_argument)
    :_mesh(receptacle),
      _filename(filename),
      _lineNum(0),
      _triangulator(triangulator),
      _nbTreatedFaces(0),
      _nbTriangulatedFaces(0)
{
    if(!triangulator)
        _triangulator = new my::EarClipping();
}

my::OffLoader::~OffLoader()
{
    delete _triangulator;
}

void my::OffLoader::load()
{
    std::string line;
    std::ostringstream oss;
    std::fstream file(_filename.c_str(), std::ios_base::in);

    if(! file.is_open() ){
        oss << "OffLoader::OffLoader: unable to open file " << _filename << std::endl;
        throw std::invalid_argument(oss.str());
    }

    //"OFF" header
    if(!_getline(file, line)){
        oss << "OffLoader::OffLoader: file " << _filename << " is empty" << std::endl;
        throw std::invalid_argument(oss.str());
    }

    if( line != std::string("OFF") ){
        if(line != "" && line[0] != '#' ){
            file.seekp(0);
        }
    }

    //Comments and blank lines
    _getMesh(file);

    file.close();

    _mesh.computeNormalsT();
    _mesh.computeNormalsV();
}
