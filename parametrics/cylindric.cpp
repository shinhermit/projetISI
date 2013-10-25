#include "cylindric.h"

void my::Cylindric::_preCylindric(const float & radius)
{
    std::ostringstream oss;

    if(radius < 0){
        oss << "Cylindric::_preCylindric: radius can not be negative" << std::endl
            << "\t given value is " << radius << std::endl;
        throw std::invalid_argument(oss.str());
    }
}

my::Cylindric::Cylindric(const float & radius, const my::Point & center)
{
    _preCylindric(radius);

    _radius = radius;
    _center = center;
}

void my::Cylindric::_preOperatorCall(const float & alpha)
{
    std::ostringstream oss;

    if( !(0. <= alpha && alpha <= 2.*glm::pi<float>()) ){
        oss << "Cylindric::_preCylindric: the angle must in radian and in range [0,2pi]" << std::endl
            << "\t given value is " << alpha << std::endl;
        throw std::invalid_argument(oss.str());
    }
}

my::Point my::Cylindric::operator()(const float & z, const float & alpha) throw(std::invalid_argument)
{
    _preOperatorCall(alpha);

    return my::Point(_radius*std::sin(alpha), z, _radius*std::cos(alpha)) + _center;
}
