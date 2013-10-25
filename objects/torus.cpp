#include "torus.h"

void my::Torus::_preTorus(const float &pathRadius, const float &tubeRadius, const int &nbSlices, const int &nbStacks)
{
    std::ostringstream oss;
    bool invalid = false;

    if(pathRadius < 0){
        oss << "my::Torus::_preTorus: path radius can not be negative" << std::endl
            << "\t given value is " << pathRadius << std::endl;
        invalid = true;
    }

    if(tubeRadius < 0){
        oss << "my::Torus::_preTorus: tube radius can not be negative" << std::endl
            << "\t given value is " << tubeRadius << std::endl;
        invalid = true;
    }

    if(nbSlices < 2){
        oss << "my::Torus::_preTorus: number of slices must be at least 2" << std::endl
            << "\t given value is " << nbSlices << std::endl;
        invalid = true;
    }

    if(nbStacks < 1){
        oss << "my::Torus::_preTorus: number of stacks must be at least 1" << std::endl
            << "\t given value is " << nbStacks << std::endl;
        invalid = true;
    }

    if(invalid)
        throw std::invalid_argument(oss.str());
}

my::Torus::Torus(const float & pathRadius, const float & tubeRadius, const int & nbSlices, const int & nbStacks)
    :ParametricMesh("Torus", 2*nbSlices, 2*(nbStacks+1)),
      _pathRadius(pathRadius),
      _tubeRadius(tubeRadius),
      _nbSlices(nbSlices),
      _nbStacks(nbStacks)
{
    _preTorus(_pathRadius, _tubeRadius, _nbSlices, _nbStacks);

    my::Toric coord(_pathRadius, _tubeRadius);

    parametricVertexInsertion(imax(), jmax(), coord);
    parametricTriangleInsertion(imax(), jmax());

    computeNormalsT();
    computeNormalsV();

}

my::Parameters my::Torus::_sampled(const int & i, const int & j)const throw(std::logic_error, std::invalid_argument)
{
    _preSampled("Torus", "path angle", "tube angle", "[0,imax()-1]", "[0, jmax()-1]", i, imax()-1, j, jmax()-1);

    float pathAngle, tubeAngle;
    float pathAngleStep, tubeAngleStep;

    pathAngleStep = my::Constant::pi / _nbSlices;
    tubeAngleStep = my::Constant::pi / (_nbStacks+1);

    pathAngle = i*pathAngleStep;
    tubeAngle = j*tubeAngleStep;

    return my::Parameters(pathAngle, tubeAngle);
}

int my::Torus::_indiceOfSampled(const int & i, const int & j)const throw(std::logic_error, std::invalid_argument)
{
    _preIndiceOfSampled("Torus", "path angle", "tube angle", "[0,imax()]", "[0, jmax()]", i, imax(), j, jmax());

    int imod;
    int jmod;

    imod = i % imax();
    jmod = j % jmax();

    return jmod + imod*jmax();
}
