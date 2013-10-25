#include "parametricmesh.h"

my::ParametricMesh::ParametricMesh(const std::string & name, const int & imax, const int & jmax)
    :TriMesh(name),
      _imax(imax),
      _jmax(jmax)
{}

void my::ParametricMesh::_preSetMax(const int &max, const std::string & setter)
{
    std::ostringstream oss;

    if(max < 0){
        oss << "ParametricMesh::" << setter << ": max sampling step value must be positive" << std::endl
            << "\t given value is " << max << std::endl;
        throw std::invalid_argument(oss.str());
    }
}

void my::ParametricMesh::setImax(const int & imax) throw(std::invalid_argument)
{
    _preSetMax(imax, "setImax");

    _imax = imax;
}

void my::ParametricMesh::setJmax(const int & jmax) throw(std::invalid_argument)
{
    _preSetMax(jmax, "setJmax");

    _jmax = jmax;
}

int my::ParametricMesh::imax() const
{
    return _imax;
}

int my::ParametricMesh::jmax() const
{
    return _jmax;
}

void my::ParametricMesh::_preSampled(const std::string & className, const std::string & sParamName, const std::string & tParamName, const std::string & sRange, const std::string & tRange, const int & i, const int & imax, const int & j, const int & jmax)const throw(std::invalid_argument)
{
    std::ostringstream oss;

    if( !(0 <= i && i <= imax) ){
        oss << className << "::_preSampled: " << sParamName << " sampling step must in range " << sRange << std::endl
            << "imax=" << imax << std::endl
            << "given value: " << i << std::endl;
        throw(std::invalid_argument(oss.str()));
    }

    if( !(0 <= j && j <= jmax) ){
        oss << className << "::_preSampled: " << tParamName << " sampling step must be in range " << tRange << std::endl
            << "jmax=" << jmax << std::endl
            << "given value: " << j << std::endl;
        throw(std::invalid_argument(oss.str()));
    }
}

my::Parameters my::ParametricMesh::_sampled(const int & m, const int & n)const throw(std::logic_error, std::invalid_argument)
{
    throw(std::logic_error("ParametricMesh::_sampled: this operation is meant to be redefined"));
}

void my::ParametricMesh::_preIndiceOfSampled(const std::string & className, const std::string & sParamName, const std::string & tParamName, const std::string & sRange, const std::string & tRange, const int & i, const int & i_max, const int & j, const int & j_max)const throw(std::invalid_argument)
{
    std::ostringstream oss;

    if( !(0 <= i && i <= _imax) ){
        oss << className << "::_preIndiceOfSampled: " << sParamName << " sampling step must in range " << sRange << std::endl
            << "imax=" << imax() << std::endl
            << "given value: " << i << std::endl;
        throw(std::invalid_argument(oss.str()));
    }

    if( !(0 <= j && j <= j_max) ){
        oss << className << "::_preIndiceOfSampled: " << tParamName << " sampling step must be in range " << tRange << std::endl
            << "jmax=" << jmax() << std::endl
            << "given value: " << j << std::endl;
        throw(std::invalid_argument(oss.str()));
    }
}

int my::ParametricMesh::indiceOfSampled(const int &m, const int &n)const
{
    return _indiceOfSampled(m,n);
}

int my::ParametricMesh::_indiceOfSampled(const int & m, const int & n)const throw(std::logic_error, std::invalid_argument)
{
    throw(std::logic_error("ParametricMesh::_indiceOfSampled: this operation is meant to be redefined"));
}

void my::ParametricMesh::parametricVertexInsertion(const int & imax, const int & jmax,
                                        my::Parametric & coord)
{
    my::Parameters param;

    for(int i=0; i<imax; ++i){
        for(int j=0; j<jmax; ++j){
            param = _sampled(i,j);
            addVertex( coord(param.first, param.second) );
        }
    }
}

void my::ParametricMesh::parametricTriangleInsertion(const int & imax, const int & jmax)
{
    int iA, iB, iC, iD;

    for(int i=0; i<imax; ++i){
        for(int j=0; j<jmax; ++j){
            iA = _indiceOfSampled(i,j);
            iB = _indiceOfSampled(i+1, j);
            iC = _indiceOfSampled(i+1, j+1);
            iD = _indiceOfSampled(i, j+1);

            addTriangle(iA, iB, iC);
            if(iA != iD){
                addTriangle(iA, iC, iD);
            }
        }
    }
}

