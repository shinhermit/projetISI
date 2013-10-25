#include "conicmesh.h"

void my::ConicMesh::_preConicMesh(const float & height, const float & aperture, const int & nbSlices, const int & nbStacks) throw(std::invalid_argument)
{
    std::ostringstream oss;
    bool invalid = false;

    if(height < 0){
        oss << "my::ConicMesh::_preConicMesh: height can not be negative" << std::endl
            << "\t given value is" << height << std::endl;
        invalid = true;
    }

    if(!(0. < aperture < 180.)){
        oss << "my::ConicMesh::_preConicMesh: The aperture angle is given in degree (for commodity reasons), in range ]0,180[" << std::endl
            << "\t given value is" << aperture << std::endl;
        invalid = true;
    }

    if(nbSlices < 2){
        oss << "my::ConicMesh::_preConicMesh: number of slices must be at least 2" << std::endl
            << "\t given value is" << nbSlices << std::endl;
        invalid = true;
    }

    if(nbStacks < 0){
        oss << "my::ConicMesh::_preConicMesh: number of stacks can not be negative" << std::endl
            << "\t given value is" << nbStacks << std::endl;
        invalid = true;
    }

    if(invalid)
        throw(std::invalid_argument(oss.str()));
}

my::ConicMesh::ConicMesh(const float & height, const float & aperture, const int & nbSlices, const int & nbStacks)
    :ParametricMesh("ConicMesh", nbStacks+2, 2*nbSlices),
      _height(height),
      _aperture(aperture),
      _nbSlices(nbSlices),
      _nbStacks(nbStacks)
{
    _preConicMesh(_height, _aperture, _nbSlices, _nbStacks);

    my::Conic coord(Point(0,-1,0), _aperture);

    parametricVertexInsertion(imax()-1, jmax(), coord);
    this->addVertex(0,-1,0);

    parametricTriangleInsertion(imax()-1, jmax());

    flipTriangles();

    computeNormalsT();
    computeNormalsV();
}

my::Parameters my::ConicMesh::_sampled(const int &i, const int &j)const throw(std::logic_error, std::invalid_argument)
{
    _preSampled("ConicMesh", "altitude", "azimut", "[0,imax()-2]", "[0, jmax()-1]", i, imax()-2, j, jmax()-1);

    float altitude, azimut;
    float altitudeStep, azimutStep;

    altitudeStep = _height/(_nbStacks+1);
    azimutStep = my::Constant::pi/_nbSlices;

    altitude = (i+1)*altitudeStep;
    azimut = j*azimutStep;

    return my::Parameters(altitude,azimut);
}

int my::ConicMesh::_indiceOfSampled(const int &i, const int &j)const throw(std::logic_error, std::invalid_argument)
{
    _preIndiceOfSampled("ConicMesh", "altitude", "azimut", "[0,imax()-1]", "[0, jmax()]", i, imax()-1, j, jmax());

    int jmod;

    if(i == 0)
        return sizeV() - 1;
    else
    {
        jmod = j % jmax();

        return jmod + (i-1)*jmax();
    }
}
