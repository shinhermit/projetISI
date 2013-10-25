#include "sphere.h"

void my::Sphere::_preSphere(const float &radius, const int &nbSlices, const int &nbStacks) throw(std::invalid_argument)
{
    std::ostringstream oss;
    bool invalid = false;

    if(radius < 0){
        oss << "my::Sphere::_preSphere: radius can not be negative" << std::endl
            << "\t given value is " << radius << std::endl;
        invalid = true;
    }

    if(nbSlices < 1){
        oss << "my::Sphere::_preSphere: number of slices must be at least 1" << std::endl
            << "\t given value is " << nbSlices << std::endl;
        invalid = true;
    }

    if(nbStacks < 1){
        oss << "my::Sphere::_preSphere: number of stacks must be at least 1" << std::endl
            << "\t given value is " << nbStacks << std::endl;
        invalid = true;
    }

    if(invalid)
        throw std::invalid_argument(oss.str());
}


my::Sphere::Sphere(const float &radius, const int &nbSlices, const int &nbStacks)
    :ParametricMesh("Sphere", nbStacks+2, 2*nbSlices),
      _radius(radius),
      _nbSlices(nbSlices),
      _nbStacks(nbStacks)
{
    _preSphere(_radius, _nbSlices, _nbStacks);

    my::Spheric coord(_radius);

    parametricVertexInsertion(imax()-2, jmax(), coord);
    this->addVertex(0,_radius,0);
    this->addVertex(0,-_radius,0);

    parametricTriangleInsertion(imax()-1, jmax());

    computeNormalsT();
    computeNormalsV();

}

my::Parameters my::Sphere::_sampled(const int &i, const int &j)const throw(std::logic_error, std::invalid_argument)
{
    _preSampled("Sphere", "polar angle", "azimut angle", "[0,imax()-2]", "[0, jmax()-1]", i, imax()-2, j, jmax()-1);

    float polar, azimut;
    float polarStep, azimutStep;

    polarStep = my::Constant::pi/(_nbStacks+1);
    azimutStep = my::Constant::pi/_nbSlices;

    polar = (i+1)*polarStep;
    azimut = j*azimutStep;

    return my::Parameters(polar,azimut);
}

int my::Sphere::_indiceOfSampled(const int & i, const int & j)const throw(std::logic_error, std::invalid_argument)
{
    _preIndiceOfSampled("Sphere", "polar angle", "azimut angle", "[0,imax()-1]", "[0, jmax()]", i, imax()-1, j, jmax());

    int jmod;

    if(i == 0)
        return sizeV() - 2; //north pole
    else if(i == _nbStacks+1)
        return sizeV()-1; //south pole
    else
    {
        jmod = j % jmax();

        return jmod + (i-1)*jmax();
    }
}
