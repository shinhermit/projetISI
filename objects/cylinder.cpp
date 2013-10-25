#include "cylinder.h"

void my::Cylinder::_preCylinder(const float &height, const float &radius, const int &nbSlices, const int &nbStacks, const int &nbCirc)
{
    std::ostringstream oss;
    bool invalid = false;

    if(height < 0){
        oss << "my::Cylinder::_preCylinder: height can not be negative" << std::endl
            << "\t given value is " << height << std::endl;
        invalid = true;
    }

    if(radius < 0){
        oss << "my::Cylinder::_preCylinder: radius can not be negative" << std::endl
            << "\t given value is " << radius << std::endl;
        invalid = true;
    }

    if(nbSlices < 2){
        oss << "my::Cylinder::_preCylinder: number of slices must be at least 2" << std::endl
            << "\t given value is " << nbSlices << std::endl;
        invalid = true;
    }

    if(nbStacks < 0){
        oss << "my::Cylinder::_preCylinder: number of stacks can not be negative" << std::endl
            << "\t given value is " << nbStacks << std::endl;
        invalid = true;
    }

    if(nbCirc < 0){
        oss << "my::Cylinder::_preCylinder: number of stacks can not be negative" << std::endl
            << "\t given value is " << nbCirc << std::endl;
        invalid = true;
    }

    if(invalid)
        throw std::invalid_argument(oss.str());
}

my::Cylinder::Cylinder(const float &height, const float &radius, const int &nbSlices, const int &nbStacks, const int &nbCirc)
    :ParametricMesh("Cylinder")
{
    _preCylinder(height, radius, nbSlices, nbStacks, nbCirc);

    my::Range baseSlaves, topSlaves, baseMasters, topMasters;
    int i, j0,j1, jmax, baseOffset, topOffset;

    my::Disk base(radius, nbSlices, nbCirc, my::Point(0, -height/2,0));
    my::Disk top(radius, nbSlices, nbCirc, my::Point(0, height/2,0));
    my::CylindricMesh tube(height, radius, nbSlices, nbStacks);

    base.flipTriangles();

    includeMesh(tube);
    includeMesh(base);
    includeMesh(top);

    /* Mesh sewing */
    jmax = 2*nbSlices;
    j0 = 0;
    j1 = jmax-1;
    baseOffset = tube.sizeV();
    topOffset = baseOffset + base.sizeV()-jmax;

    //masters
    i = 0;
    baseMasters.first = tube.indiceOfSampled(i,j0);
    baseMasters.second = tube.indiceOfSampled(i,j1);

    i = nbStacks+1;
    topMasters.first = tube.indiceOfSampled(i,j0);
    topMasters.second = tube.indiceOfSampled(i,j1);

    //slaves
    i = nbCirc+1;
    baseSlaves.first = base.indiceOfSampled(i,j0) + baseOffset;
    baseSlaves.second =  base.indiceOfSampled(i,j1) + baseOffset;

    topSlaves.first = top.indiceOfSampled(i,j0) + topOffset;
    topSlaves.second =  top.indiceOfSampled(i,j1) + topOffset;

    //sewing
    sew(baseSlaves, baseMasters);
    sew(topSlaves, topMasters);
}
