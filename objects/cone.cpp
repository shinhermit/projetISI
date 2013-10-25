#include "cone.h"

void my::Cone::_preCone(const float & height, const float & aperture, const int & nbSlices, const int & nbStacks, const int &nbCirc) throw(std::invalid_argument)
{
    std::ostringstream oss;
    bool invalid = false;

    if(height < 0){
        oss << "my::Cone::_preCone: height can not be negative" << std::endl
            << "given value is " << height << std::endl;
        invalid = true;
    }

    if(!(0. < aperture < 180.)){
        oss << "my::Cone::_preCone: The aperture angle is given in degree (for commodity reasons), in range ]0,180[" << std::endl
            << "given value is " << aperture << std::endl;
        invalid = true;
    }

    if(nbSlices < 2){
        oss << "my::Cone::_preCone: number of slices must be at least 2" << std::endl
            << "given value is " << nbSlices << std::endl;
        invalid = true;
    }

    if(nbStacks < 0){
        oss << "my::Cone::_preCone: number of stacks can not be negative" << std::endl
            << "given value is " << nbStacks << std::endl;
        invalid = true;
    }

    if(nbCirc < 0){
        oss << "my::Cone::_preCone: number of stacks can not be negative" << std::endl
            << "given value is " << nbCirc << std::endl;
        invalid = true;
    }

    if(invalid)
        throw std::invalid_argument(oss.str());
}

my::Cone::Cone(const float & height, const float & aperture, const int & nbSlices, const int & nbStacks, const int & nbCirc)
    :ParametricMesh("Cone")
{
    _preCone(height, aperture, nbSlices, nbStacks, nbCirc);

    my::Range slaves, masters;
    int i, j0,j1, jmax, offset;

    my::Disk base(height*std::tan(aperture*my::Constant::pi / 180.), nbSlices, nbCirc, my::Point(0,height/2.,0));
    my::ConicMesh cone(height, aperture, nbSlices, nbStacks);

    includeMesh(cone);
    includeMesh(base);

    /* Mesh sewing */
    jmax = 2*nbSlices;
    j0 = 0;
    j1 = jmax-1;
    offset = cone.sizeV();

    //masters
    i = nbStacks+1;
    masters.first = cone.indiceOfSampled(i,j0);
    masters.second = cone.indiceOfSampled(i,j1);

    //slaves
    i = nbCirc+1;
    slaves.first = base.indiceOfSampled(i,j0) + offset;
    slaves.second =  base.indiceOfSampled(i,j1) + offset;

    sew(slaves, masters);
}
