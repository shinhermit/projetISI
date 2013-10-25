#include "grid.h"

void my::Grid::_preGrid(const float & width, const float & length, const int &nbSdiv, const int &nbTdiv)
{
    std::ostringstream oss;
    bool invalid = false;

    if(width < 0){
        oss << "my::Grid::_preGrid: width can not be negative" << std::endl
            << "\t given value is " << width << std::endl;
        invalid = true;
    }

    if(length < 0){
        oss << "my::Grid::_preGrid: length can not be negative" << std::endl
            << "\t given value is " << length << std::endl;
        invalid = true;
    }

    if(nbSdiv < 0){
        oss << "my::Grid::_preGrid: number of slices can not be negative" << std::endl
            << "\t given value is " << nbSdiv << std::endl;
        invalid = true;
    }

    if(nbTdiv < 0){
        oss << "my::Grid::_preGrid: number of stacks can not be negative" << std::endl
            << "\t given value is " << nbTdiv << std::endl;
        invalid = true;
    }

    if(invalid)
        throw std::invalid_argument(oss.str());
}

my::Grid::Grid(const Point &A, const Vector &u, const Vector &v, const float & width, const float & length, const int &nbSdiv, const int &nbTdiv)
    :ParametricMesh("Grid", nbSdiv+2, nbTdiv+2),
      _A(A),
      _u(u),
      _v(v),
      _length(length),
      _width(width),
      _nbSlices(nbSdiv),
      _nbStacks(nbTdiv)
{
    _preGrid(_width, _length, _nbSlices, _nbStacks);

    Planar coord(_A,_u,_v);

    parametricVertexInsertion(imax(), jmax(), coord);
    parametricTriangleInsertion(imax()-1, jmax()-1);

    computeNormalsT();
    computeNormalsV();
}

my::Parameters my::Grid::_sampled(const int &i, const int &j) const throw(std::logic_error, std::invalid_argument)
{
    _preSampled("Grid", "s", "t", "[0,imax()-1]", "[0, jmax()-1]", i, imax()-1, j, jmax()-1);

    float sStep, tStep;
    float s, t;

    sStep = _width/(_nbSlices+1);
    tStep = _length/(_nbStacks+1);

    s = i*sStep;
    t = j*tStep;

    return my::Parameters(s,t);
}

int my::Grid::_indiceOfSampled(const int &i, const int &j) const throw(std::logic_error, std::invalid_argument)
{
    _preIndiceOfSampled("Grid", "s", "t", "[0,imax()-1]", "[0, jmax()-1]", i, imax()-1, j, jmax()-1);

    return j + i*jmax();
}
