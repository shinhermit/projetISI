#include "gridcube.h"

void my::GridCube::_preGridCube(const float & height, const int & nbXdiv, const int & nbYdiv, const int & nbZdiv)
{
    std::ostringstream oss;
    bool invalid = false;

    if(height < 0){
        oss << "my::GridCube::_preGridCube: height can not be negative" << std::endl
            << "\t given value is " << height << std::endl;
        invalid = true;
    }

    if(nbXdiv < 0){
        oss << "my::GridCube::_preGridCube: number of X divisions can not be negative" << std::endl
            << "\t given value is " << nbXdiv << std::endl;
        invalid = true;
    }

    if(nbYdiv < 0){
        oss << "my::GridCube::_preGridCube: number of Y divisions can not be negative" << std::endl
            << "\t given value is " << nbYdiv << std::endl;
        invalid = true;
    }

    if(nbZdiv < 0){
        oss << "my::GridCube::_preGridCube: number of Z divisions can not be negative" << std::endl
            << "\t given value is " << nbZdiv << std::endl;
        invalid = true;
    }

    if(invalid)
        throw std::invalid_argument(oss.str());
}

my::GridCube::GridCube(const float & height, const int & nbXdiv, const int & nbYdiv, const int & nbZdiv, const my::Point & center)
    :ParametricMesh("GridCube"),
      _height(height),
      _nbXdiv(nbXdiv),
      _nbYdiv(nbYdiv),
      _nbZdiv(nbZdiv),
      _center(center)
{
    _preGridCube(_height, _nbXdiv, _nbYdiv, _nbZdiv);

    int slave, master;
    int backOffset, leftOffset, rightOffset, topOffset, bottomOffset;
    int deleted;

    my::Grid front(my::Point(-height/2,-height/2,height/2), my::Vector(1,0,0), my::Vector(0,1,0), height, height, nbXdiv, nbYdiv);
    my::Grid back(my::Point(height/2,-height/2,-height/2), my::Vector(-1,0,0), my::Vector(0,1,0), height, height, nbXdiv, nbYdiv);

    my::Grid left(my::Point(-height/2,-height/2,-height/2), my::Vector(0,0,1), my::Vector(0,1,0), height, height, nbZdiv, nbYdiv);
    my::Grid right(my::Point(height/2,-height/2,height/2), my::Vector(0,0,-1), my::Vector(0,1,0), height, height, nbZdiv, nbYdiv);

    my::Grid top(my::Point(-height/2,height/2,height/2), my::Vector(1,0,0), my::Vector(0,0,-1), height, height, nbXdiv, nbZdiv);
    my::Grid bottom(my::Point(-height/2,-height/2,-height/2), my::Vector(1,0,0), my::Vector(0,0,1), height, height, nbXdiv, nbZdiv);

    includeMesh(front);
    includeMesh(back);
    includeMesh(left);
    includeMesh(right);
    includeMesh(top);
    includeMesh(bottom);

    backOffset = front.sizeV();
    leftOffset = backOffset+left.sizeV();
    rightOffset = leftOffset+right.sizeV();
    topOffset = rightOffset+top.sizeV();
    bottomOffset = topOffset+bottom.sizeV();

}
