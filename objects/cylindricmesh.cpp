#include "cylindricmesh.h"

void my::CylindricMesh::_preCylindricMesh(const float & height, const float & radius, const int & nbSlices, const int & nbStacks)
{
    std::ostringstream oss;
    bool invalid = false;

    if(height < 0){
        oss << "my::CylindricMesh::_preCylindricMesh: height can not be negative" << std::endl
            << "\t given value is " << height << std::endl;
        invalid = true;
    }

    if(radius < 0){
        oss << "my::CylindricMesh::_preCylindricMesh: radius can not be negative" << std::endl
            << "\t given value is " << radius << std::endl;
        invalid = true;
    }

    if(nbSlices < 2){
        oss << "my::CylindricMesh::_preCylindricMesh: number of slices must be at least 2" << std::endl
            << "\t given value is " << nbSlices << std::endl;
        invalid = true;
    }

    if(nbStacks < 0){
        oss << "my::CylindricMesh::_preCylindricMesh: number of stacks can not be negative" << std::endl
            << "\t given value is " << nbStacks << std::endl;
        invalid = true;
    }

    if(invalid)
        throw std::invalid_argument(oss.str());
}

my::CylindricMesh::CylindricMesh(const float & height, const float & radius, const int & nbSlices, const int & nbStacks)
    :ParametricMesh("Torus", nbStacks+2, 2*nbSlices),
      _height(height),
      _radius(radius),
      _nbSlices(nbSlices),
      _nbStacks(nbStacks)
{
    _preCylindricMesh(_height, _radius, _nbSlices, _nbStacks);

    my::Cylindric coord(_radius, my::Point(0, -height/2, 0));

    parametricVertexInsertion(imax(), jmax(), coord);
    parametricTriangleInsertion(imax()-1, jmax());

    flipTriangles();

    computeNormalsT();
    computeNormalsV();

}

my::Parameters my::CylindricMesh::_sampled(const int &i, const int &j)const throw(std::logic_error, std::invalid_argument)
{
    _preSampled("CylindricMesh", "altitude", "azimut", "[0,imax()-1]", "[0, jmax()-1]", i, imax()-1, j, jmax()-1);

    float altitude, azimut;
    float altitudeStep, azimutStep;

    altitudeStep = _height / (_nbStacks+1);
    azimutStep = my::Constant::pi / _nbSlices;

    altitude= i*altitudeStep;
    azimut = j*azimutStep;

    return my::Parameters(altitude, azimut);
}

int my::CylindricMesh::_indiceOfSampled(const int &i, const int &j)const throw(std::logic_error, std::invalid_argument)
{
    _preIndiceOfSampled("CylindricMesh", "altitude", "azimut", "[0,imax()-2]", "[0, jmax()]", i, imax()-2, j, jmax());

    int jmod;

    jmod = j % jmax();

    return jmod + i*jmax();
}
