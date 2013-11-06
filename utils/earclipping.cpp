#include "earclipping.h"

int my::EarClipping::_cyclicPrev(const int & vertex) const
{
    return (vertex + _currentPoly.size()-1) % _currentPoly.size();
}

int my::EarClipping::_cyclicNext(const int & vertex) const
{
    return (vertex + 1) % _currentPoly.size();
}

bool my::EarClipping::_convexVertex(const int & vertex)const
{
    int nextRef, prevRef, iA, iB, iC;
    my::Vertex A, B, C;
    my::Vector tv; //triangle orientation vector

    prevRef = _cyclicPrev(vertex);
    nextRef = _cyclicNext(vertex);

    iA = _currentPoly[prevRef];
    iB = _currentPoly[vertex];
    iC = _currentPoly[nextRef];

    A = _poly->vertex(iA);
    B = _poly->vertex(iB);
    C = _poly->vertex(iC);

    tv = glm::cross(B,C) + glm::cross(C,A) + glm::cross(A,B);

    return ( glm::dot(_orientation, tv) > 0 );
}

bool my::EarClipping::_insideTriangle(const my::Point & A, const my::Point & B, const my::Point & C, const my::Point & M)const
{
    my::Vector AB = glm::normalize(B - A);
    my::Vector AC = glm::normalize(C - A);
    my::Vector BC = glm::normalize(C - B);

    my::PlanarExpression orthoPlaneAB(A, AB, glm::cross(AB, AC));
    my::PlanarExpression orthoPlaneAC(A, AC, glm::cross(AB, AC));
    my::PlanarExpression orthoPlaneBC(B, BC, glm::cross(BC, -AB));

    return (orthoPlaneAB(M)*orthoPlaneAB(C) > 0
            &&
            orthoPlaneAC(M)*orthoPlaneAC(B) > 0
            &&
            orthoPlaneBC(M)*orthoPlaneBC(A) > 0
            );
}

bool my::EarClipping::_earVertex(const int & vertexRef)const
{
    // Warning! vertex must be convex first (test with _convexVertex)
    bool contains;
    int i;
    int nextRef, prevRef;

    prevRef = _cyclicPrev(vertexRef);
    nextRef = _cyclicNext(vertexRef);

    my::Point A = _poly->vertex(_currentPoly[prevRef]);
    my::Point B = _poly->vertex(_currentPoly[vertexRef]);
    my::Point C = _poly->vertex(_currentPoly[nextRef]);

    i = 0;
    contains = false;
    while(i < _currentPoly.size() && !contains)
    {
        if(i != prevRef && i != vertexRef && i != nextRef)
            contains = _insideTriangle(A, B, C, _poly->vertex(_currentPoly[i]));
        ++i;
    }

    if(contains)
        std::cout << "EarClipping::_earVertex: convex vertex " << vertexRef << " triangle contains vertex " << _currentPoly[i-1] << std::endl;

    return !contains;
}

void my::EarClipping::_buildConvexityLists()
{
    for(int i=0; i < _currentPoly.size(); ++i){
        if(_convexVertex(i)){
            if(_earVertex(i)){
                _earVertices.push_back(i);
            }
            else{
                _convexVertices.push_back(i);
            }
        }
        else{
            _reflexVertices.push_back(i);
        }
    }
}

void my::EarClipping::_addTriangle(const int & earVertex)
{
    my::Triangle triangle;
    int refA, refB, refC, A, B, C;

    refB = earVertex;
    refA = _cyclicPrev(refB);
    refC = _cyclicNext(refB);

    A = _currentPoly[refA];
    B = _currentPoly[refB];
    C = _currentPoly[refC];

    triangle.push_back(A);
    triangle.push_back(B);
    triangle.push_back(C);

    _triangulation->push_back(triangle);
}

void my::EarClipping::_checkConvexityChanges(const int & vertex)
{
    std::list<int>::iterator it;

    it = std::find(_reflexVertices.begin(), _reflexVertices.end(), vertex);
    if(it != _reflexVertices.end()){
        if( _convexVertex(vertex) ){
            _reflexVertices.erase(it);

            if(_earVertex(vertex)){
                _earVertices.push_back(vertex);
            }
            else{
                _convexVertices.push_back(vertex);
            }
        }
    }

    else{
        std::deque<int>::iterator it = std::find(_earVertices.begin(), _earVertices.end(), vertex);
        if(it != _earVertices.end()){
            if(!_earVertex(vertex)){
                _earVertices.erase(it);
                _convexVertices.push_back(vertex);
            }
        }
    }
}

void my::EarClipping::_renumberLists(const int & earVertex)
{
    std::list<int>::iterator it;

    it=_convexVertices.begin();
    while(it != _convexVertices.end()){
        if(*it > earVertex){
            *it -= 1;
            ++it;
        }
        else if(*it == earVertex){
            _convexVertices.erase(it++);
        }
        else
            ++it;
    }

    it=_reflexVertices.begin();
    while(it != _reflexVertices.end()){
        if(*it > earVertex){
            *it -= 1;
            ++it;
        }
        else if(*it == earVertex){
            _reflexVertices.erase(it++);
        }
        else
            ++it;
    }

    for(std::deque<int>::iterator it=_earVertices.begin(); it != _earVertices.end(); ++it){
        if(*it > earVertex)
            *it -= 1;
    }
}

void my::EarClipping::_updateLists(const int & earVertex)
{
    int prev, next;

    prev = _cyclicPrev(earVertex);
    next = _cyclicNext(earVertex);

    _currentPoly.erase(_currentPoly.begin()+earVertex);

    _renumberLists(earVertex);
    if(prev > earVertex) --prev;
    if(next > earVertex) --next;

    _checkConvexityChanges(prev);
    _checkConvexityChanges(next);
}

void my::EarClipping::_preProcess(const my::IPolygon & poly) throw(std::invalid_argument)
{
    std::ostringstream oss;

    if(! poly.size() >= 3){
        oss << "EarClipping::_preProcess: polygon must have at least 3 vertices." << std::endl
            << "\t given polygon size is " << poly.size() << std::endl;

        throw std::invalid_argument(oss.str());
    }
}

void my::EarClipping::_clearLists()
{
    _currentPoly.clear();
    _convexVertices.clear();
    _reflexVertices.clear();
    _earVertices.clear();
}

void my::EarClipping::_init(const my::IPolygon & poly, std::vector<my::Triangle> & triangulation)
{
    _poly = &poly;
    _orientation = poly.orientationVector();
    _triangulation = &triangulation;

    _clearLists();

    for(int i = 0; i < poly.size(); ++i)
        _currentPoly.push_back(i);
}

my::EarClipping::EarClipping()
{}

void my::EarClipping::process(const my::IPolygon & poly, std::vector<my::Triangle> & triangulation)
{
    _preProcess(poly);

    int earVertex;
    _init(poly, triangulation);

    _buildConvexityLists();

    while(_earVertices.size() > 0 && _currentPoly.size() >= 3){
        earVertex = _earVertices.front();

        _addTriangle(earVertex);

        _updateLists(earVertex);

        _earVertices.pop_front();
    }
}

