#include "diskhole.h"

void my::DiskHole::_preDiskHole(const float & bigRadius, const float & smallRadius, const int & nbSlices, const int & nbCirc) throw(std::invalid_argument)
{
    std::ostringstream oss;
    bool invalid = false;

    if(smallRadius < 0){
        oss << "my::DiskHole::_preDiskHole: small radius can not be negative" << std::endl
            << "\t given value is " << smallRadius << std::endl;
        invalid = true;
    }

    if(bigRadius < 0){
        oss << "my::DiskHole::_preDiskHole: big radius can not be negative" << std::endl
            << "\t given value is " << bigRadius << std::endl;
        invalid = true;
    }

    if(nbSlices < 2){
        oss << "my::DiskHole::_preDiskHole: number of slices must be at least 2" << std::endl
            << "\t given value is " << nbSlices << std::endl;
        invalid = true;
    }

    if(nbCirc < 0){
        oss << "my::DiskHole::_preDiskHole: number of stacks can not be negative" << std::endl
            << "\t given value is " << nbCirc << std::endl;
        invalid = true;
    }

    if(invalid)
        throw std::invalid_argument(oss.str());
}

my::DiskHole::DiskHole(const float & bigRadius, const float & smallRadius, const int & nbSlices, const int & nbCirc)
    :ParametricMesh("DiskHole", nbCirc+2, 2*nbSlices),
      _bigRadius(bigRadius),
      _smallRadius(smallRadius),
      _nbSlices(nbSlices),
      _nbCirc(nbCirc)
{
    _preDiskHole(_bigRadius, _smallRadius, _nbSlices, _nbCirc);

    Circular coord(_bigRadius);

    parametricVertexInsertion(imax(), jmax(), coord);
    parametricTriangleInsertion(imax()-1, jmax());

    computeNormalsT();
    computeNormalsV();
}

my::Parameters my::DiskHole::_sampled(const int & i, const int & j)const throw(std::logic_error, std::invalid_argument)
{
    _preSampled("DiskHole", "distance", "azimut angle", "[0,imax()]", "[0, jmax()]", i, imax(), j, jmax());

    float distance, azimut;
    float angleStep, radiusStep;

    angleStep = my::Constant::pi/_nbSlices; //2pi/2n = pi/n
    radiusStep = (_bigRadius - _smallRadius) / (_nbCirc+1);

    distance = _smallRadius + i*radiusStep;
    azimut = j*angleStep;

    return my::Parameters(distance, azimut);
}

int my::DiskHole::_indiceOfSampled(const int & i, const int & j)const throw(std::logic_error, std::invalid_argument)
{
    _preIndiceOfSampled("DiskHole", "distance", "azimut angle", "[0,imax()-1]", "[0, jmax()]", i, imax()-1, j, jmax());

    int jmod;

    jmod = j % jmax();

    return jmod + i*jmax();
}
