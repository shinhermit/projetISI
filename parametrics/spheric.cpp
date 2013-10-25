#include "spheric.h"

void my::Spheric::_preSpheric(const float &radius)
{
    std::ostringstream oss;

    if(radius < 0){
        oss << "Spheric::_preSpheric: radius can not be negative" << std::endl
            << "\t given value is " << radius << std::endl;
        throw std::invalid_argument(oss.str());
    }
}

my::Spheric::Spheric(const float & radius)
{
    _preSpheric(radius);

    _radius = radius;
}

void my::Spheric::_preOperatorCall(const float &polar, const float &azimutal)
{
    std::ostringstream oss;

    if( !(0. <= polar && polar <= 2.*glm::pi<float>() && 0. <= azimutal && azimutal <= 2.*glm::pi<float>()) ){
        oss << "Spheric::Spheric::_preOperatorCall: Angles must be in radian and in range [0, 2pi]" << std::endl
            << "\t given polar is " << polar << std::endl
            << "\t given azimutal is " << azimutal << std::endl;
        throw std::invalid_argument(oss.str());
    }
}

my::Point my::Spheric::operator()(const float & polar, const float & azimutal) throw(std::invalid_argument)
{
    _preOperatorCall(polar, azimutal);

    return my::Point(_radius*std::sin(polar)*std::sin(azimutal),
                 _radius*std::cos(polar),
                     _radius*std::sin(polar)*std::cos(azimutal));
}
