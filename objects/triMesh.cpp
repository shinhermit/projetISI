#include "triMesh.h"

#include <glm/gtc/type_ptr.hpp>

TriMesh::TriMesh(const string &name)
    : Object3D(name)
{}

void TriMesh::addVertex(my::Vertex v)
{
  extendBoundingBox(v);
  _vertices.push_back(v);
}


void TriMesh::addVertex(double x, double y, double z){
  addVertex(my::Vertex(x,y,z));
}


void TriMesh::addTriangle(my::Triangle t){
  _triangles.push_back(t);
}

void TriMesh::addTriangle(int v1, int v2, int v3){
  my::Triangle t;
  t.push_back(v1);
  t.push_back(v2);
  t.push_back(v3);
  addTriangle(t);
}

void TriMesh::_preSetColor(const int & indice, const int & maxIndice, const Color & color, const string & methodName, const std::string & range) throw(std::invalid_argument)
{
    std::ostringstream oss;
    bool invalid = false;

    if(! (0 <= indice && indice < maxIndice)){
        oss << "TriMesh::_preSetColor (for " << methodName << "): given indice is out of range " << range << std::endl
            << "\t given indice is " << indice << std::endl
            << "\t sizeV() is " << maxIndice << std::endl;
        invalid = true;
    }

    if(! (0 <= color[0] && color[0] <= 1
          &&
          0 <= color[1] && color[1] <= 1
          &&
          0 <= color[2] && color[2] <= 1
          &&
          0 <= color[3] && color[3] <= 1)){
        oss << "TriMesh::_preSetColor (for " << methodName << "): given color is not a valid color. RGBA Color components are float in range [0,1]" << std::endl
            << "\t given color is R=" << color[0] << " G=" << color[1] << " B=" << color[2] << " A=" << color[3] << std::endl;
        invalid = true;
    }

    if(invalid)
        throw std::invalid_argument(oss.str());
}

void TriMesh::setVertexColor(const int & vertex, const my::Color & color)
{
    _preSetColor(vertex, sizeV(), color, "setVertexColor", "[0,sizeV()]");
    _colors[vertex] = color;
}

void TriMesh::setVertexColor(const int & vertex, const float & R, const float & G, const float & B, const float & A)
{
    setVertexColor(vertex, my::Color(R,G,B,A));
}

void TriMesh::setTriangleColor(const int & t, const my::Color & color)
{
    _preSetColor(t, sizeT(), color, "setTriangleColor", "[0,sizeT()]");
    for(int i=0; i < _triangles[t].size(); ++i){
        const int & vertex = _triangles[t][i];
        _colors[vertex] = color;
    }
}

void TriMesh::setTriangleColor(const int & t, const float & R, const float & G, const float & B, const float & A)
{
    setTriangleColor(t, my::Color(R,G,B,A));
}

void TriMesh::addNormalT(my::Normal n){
  _normalsT.push_back(n);
}
void TriMesh::addNormalV(my::Normal n){
    _normalsV.push_back(n);
}

void TriMesh::includeMesh(const TriMesh & mesh)
{
    my::Triangle triangle(3);
    int offset = sizeV();


    for(std::vector<my::Vertex>::const_iterator it=mesh._vertices.begin();
        it != mesh._vertices.end();
        ++it)
    {
        _vertices.push_back(*it);
    }

    for(std::vector<my::Triangle>::const_iterator it=mesh._triangles.begin();
        it != mesh._triangles.end();
        ++it)
    {
        //translate indices
        for(int i=0; i<3; ++i)
            triangle[i] = it->at(i) + offset;

        _triangles.push_back(triangle);
    }

    for(std::vector<my::Normal>::const_iterator it=mesh._normalsT.begin();
        it != mesh._normalsT.end();
        ++it)
    {
        _normalsT.push_back(*it);
    }

    for(std::vector<my::Normal>::const_iterator it=mesh._normalsV.begin();
        it != mesh._normalsV.end();
        ++it)
    {
        _normalsV.push_back(*it);
    }
}

void TriMesh::loadOffFile(const string & filename, my::IPolygonTriangulator * triangulator)
{
    my::OffLoader off(*this, filename, triangulator);
    off.load();
}

void TriMesh::_preCollapseVertices(const int &slave, const int &master) throw(std::invalid_argument)
{
    std::ostringstream oss;

    if(!(0 <= slave && slave < _vertices.size())){
        oss << "TriMesh::_preCollapseVertices: slave vertex indice is out fo range" << std::endl
            << "range is [0, sizeV()[ with sizeV()=" << _vertices.size() << std::endl
            << "given slave indice is " << slave << std::endl;
        throw std::invalid_argument(oss.str());
    }

    if(!(0 <= master && master < _vertices.size())){
        oss << "TriMesh::_preCollapseVertices: master vertex indice is out fo range" << std::endl
            << "range is [0, sizeV()[ with sizeV()=" << _vertices.size() << std::endl
            << "given master indice is " << master << std::endl;
        throw std::invalid_argument(oss.str());
    }

    if(!(slave != master)){
        oss << "TriMesh::_preCollapseVertices: slave indice and master indice must be different" << std::endl;
        throw std::invalid_argument(oss.str());
    }
}

void TriMesh::collapseVertices(const int & slave, const int & master, bool computeNormals)
{
    /*Algorithme:
      Parcourir les triangles:
        Parcourir les sommets du triangle
          SI le numéro du sommet courant est == slave
            remplacer le sommet courant, qui est slave, par master
            SI, par suite, master apparaît 2 fois dans le triangle, supprimer le triangle

      Supprimer slave

      Parcourir les triangles:
        Parcourir les sommets du triangle
           SI le numéro du sommet est > slave, renuméroter le sommet (-1)

      Recalculer les normales
      */

    _preCollapseVertices(slave, master);

    bool collapsedTriangle;

    collapsedTriangle = false;
    std::vector<my::Triangle>::iterator it = _triangles.begin();
    while(it != _triangles.end())
    {
        int i=0;
        while(i < 3 && !collapsedTriangle)
        {
            if(it->at(i) == slave){
                it->at(i) = master;
                if( it->at((i+1)%3) == master || it->at((i+2)%3) == master ){
                    collapsedTriangle = true;
                }
                else
                    ++i;
            }
            else
                ++i;
        }

        if(collapsedTriangle){
            _triangles.erase(it++);
            collapsedTriangle = false;
        }
        else
            ++it;
    }

    _vertices.erase(_vertices.begin()+slave);

    for(std::vector<my::Triangle>::iterator iter = _triangles.begin();
        iter != _triangles.end();
        ++iter)
    {
        for(int i=0; i<3; ++i)
            if(iter->at(i) > slave)
                iter->at(i) = iter->at(i) - 1;
    }

    if(computeNormals)
    {
        computeNormalsT();
        computeNormalsV();
    }
}

void TriMesh::_preSew(const my::Range &slaves, const my::Range &masters) throw(std::invalid_argument)
{
    std::ostringstream oss;
    bool invalid = false;

    //indices must be positive
    if(!(slaves.first >= 0 && slaves.second >= 0))
    {
        oss << "TriMesh::_preSew: indices in slaves range can not be negative" << std::endl
            << "\t given slaves range is [" << slaves.first << ", " << slaves.second << "]" << std::endl;
        invalid = true;
    }

    if(!(masters.first >= 0 && masters.second >= 0))
    {
        oss << "TriMesh::_preSew: indices in masters range can not be negative" << std::endl
            << "\t given masters range is [" << masters.first << ", " << masters.second << "]" << std::endl;
        invalid = true;
    }

    //range second >= range first
    if( !(slaves.first <= slaves.second) )
    {
        oss << "TriMesh::_preSew: invalid slaves range; range scheme is [min,Max]" << std::endl
            << "\t given slaves range is [" << slaves.first << ", " << slaves.second << "]" << std::endl;
        invalid = true;
    }

    if( !(masters.first <= masters.second) )
    {
        oss << "TriMesh::_preSew: invalid masters range; range scheme is [min,Max]" << std::endl
            << "\t given masters range is [" << masters.first << ", " << masters.second << "]" << std::endl;
        invalid = true;
    }

    //length master >= length slave
    if( !(masters.second-masters.first >= slaves.second-slaves.first) )
    {
        oss << "TriMesh::_preSew: master range must have equal or more indices than slave range" << std::endl
            << "\t given slaves range is [" << slaves.first << ", " << slaves.second << "]" << std::endl
            << "\t given masters range is [" << masters.first << ", " << masters.second << "]" << std::endl;
        invalid = true;
    }

    if(invalid)
        throw(std::invalid_argument(oss.str()));
}

void TriMesh::sew(const Range &slaves, const Range &masters)
{
    _preSew(slaves, masters);

    int i, j;
    int imax, jmax;

    i = slaves.first;
    j = masters.first;
    imax = slaves.second;
    jmax = masters.second;

    while(i <= imax && j <= jmax)
    {
        collapseVertices(i,j);

        --imax;
        if(jmax > i)
            --jmax;
        else
            ++j;
    }
    computeNormalsT();
    computeNormalsV();
}

void TriMesh::flipTriangles()
{
    int temp;

    for(std::vector<my::Triangle>::iterator it=_triangles.begin();
        it != _triangles.end();
        ++it)
    {
        temp = it->at(1);
        it->at(1) = it->at(2);
        it->at(2) = temp;
    }

    computeNormalsT();
    computeNormalsV();
}

int TriMesh::sizeV() const
{
    return _vertices.size();
}

int TriMesh::sizeT() const
{
    return _triangles.size();
}


my::Vertex TriMesh::getVertex(const int & i)const
{
  return _vertices.at(i);
}


void TriMesh::computeBoundingBox(){
  if(_vertices.size()<1) return;

  _bBoxMax=_vertices[0];
  _bBoxMin=_vertices[0];
  for(unsigned int i=0; i<_vertices.size(); ++i)
    extendBoundingBox(_vertices[i]);
}

void TriMesh::computeNormalsT(){
    // Compute a normal for each triangle
    // and put it in normalsT vector.

    my::Point A, B, C;
    my::Vector u,v;
    my::Normal n;

    _normalsT.clear();

    for(unsigned int t=0; t<_triangles.size(); ++t) {
        A = _vertices[_triangles[t][0]];
        B = _vertices[_triangles[t][1]];
        C = _vertices[_triangles[t][2]];

        u = B-A;
        v = C-A;

        n = glm::normalize( glm::cross(u,v) );
        addNormalT(n);
    }
    assert(_normalsT.size() == _triangles.size());
}


void TriMesh::computeNormalsV(float angle_threshold){
    // Compute a normal for each vertex of each triangle
    // and put it in normalsV vector.
    // Each normal is the average of adjacent triangle normals.
    // Only normals whose angle with the current triangle normal
    // is below the angle_threshold is taken into account.

    // the algorithm below favors speed rather than memory


      my::Normal n,m, sum;
      std::map<int,std::vector<int> > adjacenceList;
      std::map<int,std::vector<int> >::iterator pos;
      std::vector<int>::iterator it;
      unsigned int vertex;
      unsigned int i;
      short j;

      _normalsV.clear();

      if(_normalsT.empty() && !_triangles.empty())
          computeNormalsT();

      for(i=0; i<_triangles.size(); ++i){
          for(j=0; j<_triangles[i].size(); ++j){
              vertex = _triangles[i][j];
              pos = adjacenceList.find(vertex);
              if( pos == adjacenceList.end() )
                  pos = adjacenceList.insert( std::pair<int,std::vector<int> >(vertex, std::vector<int>()) ).first;
              pos->second.push_back(i);
          }
      }

      for(i=0; i<_triangles.size(); ++i){
          n = _normalsT[i];
          for(j=0; j<_triangles[i].size(); ++j){
              sum = n;
              vertex = _triangles[i][j];
              std::vector<int> & adjacentTriangles = adjacenceList[vertex];
              for(it=adjacentTriangles.begin();
                  it != adjacentTriangles.end();
                  ++it){
                  m = _normalsT[*it];
                  if( *it != i && glm::angle(n,m) < angle_threshold ){
                      sum += m;
                  }
              }
              addNormalV(glm::normalize(sum));
          }
      }
}

double TriMesh::normalize(){
  glm::vec3 size=_bBoxMax-_bBoxMin;
  glm::vec3 c=getBoundingBoxCenter();
  double scale=2/max(size.x, max(size.y,size.z));

  for(unsigned int i=0; i<_vertices.size(); ++i){
      _vertices[i]+=c;
      _vertices[i]*=scale;
    }

  _bBoxMin+=c;
  _bBoxMin*=scale;
  _bBoxMax+=c;
  _bBoxMax*=scale;

  return scale;
}


std::string TriMesh::toString(){
  ostringstream oss;
  oss<< "["<< _name <<" v:"<< _vertices.size() <<", t:"<< _triangles.size() <<"]";
  return oss.str();
}

void TriMesh::toOStream(std::ostream& out) const{
  Object3D::toOStream(out);
  out << "   v: " << _vertices.size()  << std::endl;
  out << "   t: " << _triangles.size() << std::endl;
}



void TriMesh::draw(bool flipnormals){
  unsigned int i,t;
  bool smooth;
  my::Normal n;
  std::map<int,my::Color>::iterator it;

  GLint mode[1];
  glGetIntegerv(GL_SHADE_MODEL, mode);
  smooth= mode[0]==GL_SMOOTH && _normalsV.size()==_triangles.size()*3;

  if(_triangles.empty())
      drawVertices();

  if(smooth){
      glBegin(GL_TRIANGLES);
      for(t=0; t<_triangles.size(); ++t)
        for(i=0; i<3; i++){
            n=_normalsV[3*t+i];
            if(flipnormals) n*=-1;

            it = _colors.find(_triangles[t][i]);
            if(it != _colors.end())
                glColor4f(it->second[0], it->second[1], it->second[2], it->second[3]);

            glNormal3fv(glm::value_ptr(n));
            glVertex3fv(glm::value_ptr(_vertices[_triangles[t][i]]));
          }
      glEnd();
    }else{
      glBegin(GL_TRIANGLES);
      for(t=0; t<_triangles.size(); ++t){
          n=_normalsT[t];
          if(flipnormals) n*=-1;
          glNormal3fv(glm::value_ptr(n));
          for(i=0; i<3; i++){
              it = _colors.find(_triangles[t][i]);
              if(it != _colors.end())
                  glColor4f(it->second[0], it->second[1], it->second[2], it->second[3]);

              glVertex3fv(glm::value_ptr(_vertices[_triangles[t][i]]));
          }
        }
      glEnd();
    }

}


void TriMesh::drawNormals(bool flipnormals){
  unsigned int i,t;
  bool smooth;
  glm::vec3 p,n;

  GLint mode[1];
  glGetIntegerv(GL_SHADE_MODEL, mode);
  smooth= mode[0]==GL_SMOOTH && _normalsV.size()==_triangles.size()*3;

  glColor3f(1,1,1);
  if(smooth){
      for(i=0; i<_normalsV.size(); ++i){
          n=_normalsV[i];
          if(flipnormals) n*=-1;
          glNormal3fv(glm::value_ptr(n));
          n/=10;
          glBegin(GL_LINES);
          glVertex3fv(glm::value_ptr(_vertices[_triangles[i/3][i%3]]));
          glVertex3fv(glm::value_ptr(_vertices[_triangles[i/3][i%3]]+n));
          glEnd();
        }
    }else{
      for(t=0; t<_triangles.size(); ++t){
          p=  _vertices[_triangles[t][0]]
              +_vertices[_triangles[t][1]]
              +_vertices[_triangles[t][2]];
          p/=3;
          n=_normalsT[t];
          if(flipnormals) n*=-1;
          glNormal3fv(glm::value_ptr(n));
          n/=10;
          glBegin(GL_LINES);
          glVertex3fv(glm::value_ptr(p));
          glVertex3fv(glm::value_ptr(p+n));
          glEnd();
        }
    }
}

void TriMesh::drawVertices(){
  glPointSize(3.);
  glBegin(GL_POINTS);
  for(unsigned int i=0; i<_vertices.size(); ++i )
    glVertex3fv(glm::value_ptr(_vertices[i]));
  glEnd();
}
