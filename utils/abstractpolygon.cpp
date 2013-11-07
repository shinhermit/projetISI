#include "abstractpolygon.h"

void my::AbstractPolygon::_preIndice(const int & i, const std::string & methodName)const throw(std::out_of_range)
{
    std::ostringstream oss;

    if(!(0<= i && i < size())){
        oss << "AbstractPolygon::_preIndice (for " << methodName << "): given indice is out of range [O,polygon_size]" << std::endl
            << "\t polygon size is " << size() << std::endl;

        throw std::out_of_range(oss.str());
    }

}

my::Vector my::AbstractPolygon::edgeVector(const int & i)const throw(std::out_of_range)
{
    _preIndice(i, "_preEdgeVector");

    my::Vertex A, B;

    A = vertex(i);
    B = vertex((i+1)%size());

    return my::Vector(B[0]-A[0],
                      B[1]-A[1],
                      B[2]-A[2]);
}

int my::AbstractPolygon::next(const int & vertex) const throw(std::out_of_range)
{
    _preIndice(vertex, "nextVertex");

    return (vertex+1) % size();
}

int my::AbstractPolygon::prev(const int & vertex) const throw(std::out_of_range)
{
    _preIndice(vertex, "prevVertex");

    return (vertex + size()-1) % size(); //minus 1 in cyclic group actually plus MAX-1
}

void my::AbstractPolygon::_prePolygon(const std::string & method)const throw(std::runtime_error)
{
    std::ostringstream oss;

    if(size() < 3){
        oss << "AbstractPolygon::_prePolygon (in AbstractPolygon::" << method << "): polygon must have at least 3 vertices in odrer to compoute base plane" << std::endl
            << "\t polygon size is " << size() << std::endl;

        throw std::runtime_error(oss.str());
    }
}

my::Planar my::AbstractPolygon::basePlane()const
{
    _prePolygon("basePlane");

    return my::Planar(vertex(0), edgeVector(0), edgeVector(1));
}

my::PlanarExpression my::AbstractPolygon::basePlaneExpression()const
{
    _prePolygon("basePlaneExpression");

    return my::PlanarExpression(vertex(0), edgeVector(0), edgeVector(1));
}

my::Vector my::AbstractPolygon::orientationVector() const
{
    _prePolygon("orientationVector");

    my::Vector crossSum;

    crossSum = my::Vector(0,0,0);
    for(int i=0; i < size()-1; ++i){
        crossSum += glm::cross( edgeVector(i), edgeVector(i+1) );
    }

    return crossSum;
}

float my::AbstractPolygon::signedArea(const my::Vector & sightingVector)const
{
    _prePolygon("signedArea");

    my::Vector N, choeLace;

    N = glm::normalize(orientationVector());

    if(glm::dot(N, sightingVector) < 0)
        N = -N;

    choeLace = my::Vector(0,0,0);
    for(int i=0; i < size(); ++i){
        choeLace += glm::cross( vertex(i), vertex((i+1)%size()) ); //point are vector too (P is vec(OP) where O is the origin
    }

    return glm::dot(N, choeLace) / 2;
}

float my::AbstractPolygon::area()const
{
    return std::abs( signedArea(glm::cross(edgeVector(0), edgeVector(1))) );
}

my::Orientation my::AbstractPolygon::orientation(const my::Vector & sightingVector)const
{
    my::Orientation wiseness;

    wiseness = ( glm::dot(orientationVector(), sightingVector) < 0 ) ? my::CLOCKWISE : my::COUNTER_CLOCKWISE;

    return wiseness;
}

float my::AbstractPolygon::circumference()const
{
    int i;
    float sum;

    sum = 0;
    for(i=0; i<size(); ++i){
        sum += glm::length(edgeVector(i));
    }

    return sum;
}

std::string my::AbstractPolygon::toString() const
{
    std::ostringstream oss;

    oss << "<";
    if(size() > 0)
        oss << "{" << vertex(0)[0] << ", " << vertex(0)[1] << ", " << vertex(0)[2] << "}";
    for(int i=1; i < size(); ++i){
        oss << ", " << "{" << vertex(i)[0] << ", " << vertex(i)[1] << ", " << vertex(i)[2] << "}";
    }
    oss << ">";

    return oss.str();
}
