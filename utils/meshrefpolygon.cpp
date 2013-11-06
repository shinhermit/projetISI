#include "meshrefpolygon.h"

my::MeshRefPolygon::MeshRefPolygon(const my::IMesh & mesh)
    :_mesh(mesh)
{}

void my::MeshRefPolygon::addVertex(const my::Vertex & vertex)
{
    throw std::logic_error("MeshRefPolygon::addVertex(const my::Vertex&): MeshRefPolygon is a dummy Polygon type used to reference a list of vertice in a mesh that need to be treated as a polygon.\n\t Thus it must not add real vertices by it's own.\n\t Use MeshRefPolygon::addRef(const int & ref) to add a reference to a vertex of the underlying mesh.");
}

void my::MeshRefPolygon::addVertex(const float & x, const float & y, const float & z)
{
    throw std::logic_error("MeshRefPolygon::addVertex(const float&, const float&, const float&): MeshRefPolygon is a dummy Polygon type used to reference a list of vertice in a mesh that need to be treated as a polygon.\n\t Thus it must not add real vertices by it's own.\n\t Use MeshRefPolygon::addRef(const int & ref) to add a reference to a vertex of the underlying mesh.");
}

void my::MeshRefPolygon::_preAddref(const int & ref) throw(std::invalid_argument)
{
    std::ostringstream oss;
    bool invalid = false;

    //check for indice range
    if(! (0 <= ref && ref < _mesh.sizeV()) ){
        oss << "MeshRefPolygon::_preAddVertex: given ref is out of range in reference mesh." << std::endl
            << "\t given ref is " << ref << std::endl
            << "\t mesh size is " << _mesh.sizeV() << std::endl;

        invalid = true;
    }

    //check for planar property
//    if(_vertexRefs.size() >= 3){
//        my::PlanarExpression planeExpression = basePlaneExpression();

//        if( planeExpression(_mesh.getVertex(ref)) > my::Constant::floatPrecision ){
//            oss << "MeshRefPolygon::_preAddVertex: inserting given vertex would break polygon planarity." << std::endl
//                << "\t given ref is " << ref << std::endl
//                << "\t mesh size is " << _mesh.sizeV() << std::endl;

//            invalid = true;
//        }
//    }

    if(invalid)
        throw std::invalid_argument(oss.str());
}

void my::MeshRefPolygon::addRef(const int & ref)
{
    _preAddref(ref);

    _vertexRefs.push_back(ref);
}

void my::MeshRefPolygon::_preIndice(const int & ref, const std::string & method)const throw(std::out_of_range)
{
    std::ostringstream oss;

    if(! (0 <= ref && ref < _vertexRefs.size())){
        oss << "MeshRefPolygon::_preIndice (for " << method << "): indice out of range." << std::endl
            << "\t given indice is " << ref << std::endl
            << "\t current polygon size is " << _vertexRefs.size() << std::endl;

        throw std::out_of_range(oss.str());
    }
}

void my::MeshRefPolygon::removeVertex(const int & i) throw(std::out_of_range)
{
    _preIndice(i, "MeshRefPolygon::removeVertex");

    _vertexRefs.erase(_vertexRefs.begin()+i);
}

void my::MeshRefPolygon::clear()
{
    _vertexRefs.clear();
}

int my::MeshRefPolygon::size()const
{
    return _vertexRefs.size();
}

my::Vertex my::MeshRefPolygon::vertex(const int & i)const throw(std::out_of_range)
{
    _preIndice(i, "MeshRefPolygon::vertex");

    return _mesh.getVertex(_vertexRefs[i]);
}

int my::MeshRefPolygon::vertexRef(const int &i) const throw(std::out_of_range)
{
    _preIndice(i, "MeshRefPolygon::vertexRef");

    return _vertexRefs.at(i);
}

std::string my::MeshRefPolygon::toString() const
{
    std::ostringstream oss;

    oss << "actual vertices: " << my::AbstractPolygon::toString() << std::endl;
    oss << "references: ";

    oss << "<";
    if(size() > 0)
        oss << vertexRef(0);
    for(int i=1; i < _vertexRefs.size(); ++i){
        oss << ", " << vertexRef(i);
    }
    oss << ">";

    return oss.str();
}
