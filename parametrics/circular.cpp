#include "circular.h"


void my::Circular::_preCircular(const float & radius)
{
    std::ostringstream oss;

    if(radius < 0)
    {
        oss << "Circular::_preCircular: radius can not be negative" << std::endl
            << "\t given value is " << radius << std::endl;
        throw std::invalid_argument(oss.str());
    }
}

my::Circular::Circular(const float &radius, const my::Point & center)
{
    _preCircular(radius);
    _radius = radius;
    _center = center;
}

void my::Circular::_preOperatorCall(const float &distance, const float &azimut) throw(std::invalid_argument)
{
    std::ostringstream oss;

    if( !(0. <= azimut && azimut <= 2.*my::Constant::pi && 0. <= distance && distance <= _radius) )
    {
        oss << "Circular::_preOperatorCall: Angles must be in radian and in range [0, 2pi]\n\t distance must less than or equal to constructed max radius" << std::endl
            << "\t max radius is " << _radius << std::endl
            << "\t max angle 2pi is " << 2.*my::Constant::pi << std::endl
            << "\t given distance is " << distance << std::endl
            << "\t given azimut is " << azimut << std::endl;

        throw std::invalid_argument(oss.str());
    }
}

my::Point my::Circular::operator()(const float & distance, const float & azimut) throw(std::invalid_argument)
{
    _preOperatorCall(distance, azimut);

    return my::Point(distance*std::sin(azimut),
                     0,
                     distance*std::cos(azimut))+_center;
}
