#include "disk.h"

void my::Disk::_preDisk(const float & radius, const int & nbSlices, const int & nbCirc) throw(std::invalid_argument)
{
    std::ostringstream oss;
    bool invalid = false;

    if(radius < 0){
        oss << "my::Disk::_preDisk: radius can not be negative" << std::endl
            << "\t given value is " << radius << std::endl;
        invalid = true;
    }

    if(nbSlices < 2){
        oss << "my::Disk::_preDisk: number of slices must be at least 2" << std::endl
            << "\t given value is " << nbSlices << std::endl;
        invalid = true;
    }

    if(nbCirc < 0){
        oss << "my::Disk::_preDisk: number of circular divisions can not be negative" << std::endl
            << "\t given value is " << nbCirc << std::endl;
        invalid = true;
    }

    if(invalid)
        throw std::invalid_argument(oss.str());
}

my::Disk::Disk(const float & radius, const int & nbSlices, const int & nbCirc, const my::Point & center)
    :ParametricMesh("DiskHole", nbCirc+2, 2*nbSlices),
      _radius(radius),
      _nbSlices(nbSlices),
      _nbCirc(nbCirc)
{
    _preDisk(_radius, _nbSlices, _nbCirc);

    Circular coord(_radius, center);

    parametricVertexInsertion(imax()-1, jmax(), coord);
    this->addVertex(center); // the center
    parametricTriangleInsertion(imax()-1, jmax());

    computeNormalsT();
    computeNormalsV();
}

my::Parameters my::Disk::_sampled(const int & i, const int & j)const throw(std::logic_error, std::invalid_argument)
{
    _preSampled("Disk", "distance", "azimut angle", "[0,imax()-2]", "[0, jmax()]", i, imax()-2, j, jmax());

    float distance, azimut;
    float angleStep, radiusStep;

    angleStep = my::Constant::pi/_nbSlices; //2pi/2n = pi/n
    radiusStep = _radius / (_nbCirc+1);

    distance = (i+1)*radiusStep;
    azimut = j*angleStep;

    return my::Parameters(distance, azimut);
}

int my::Disk::_indiceOfSampled(const int & i, const int & j)const throw(std::logic_error, std::invalid_argument)
{
    _preIndiceOfSampled("Disk", "distance", "azimut angle", "[0,imax()-1]", "[0, jmax()]", i, imax()-1, j, jmax());

    int jmod;

    if(i == 0)
        return sizeV() - 1;
    else
    {
        jmod = j % jmax();
        return jmod + (i-1)*jmax();
    }
}
