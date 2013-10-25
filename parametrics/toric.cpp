#include "toric.h"

void my::Toric::_preToric(const float & pathRadius, const float & tubeRadius)
{
    std::ostringstream oss;
    bool invalid = false;

    if(pathRadius < 0){
        oss << "Toric::_preToric: path radius can not be negative" << std::endl
            << "\t given value is " << pathRadius << std::endl;
        invalid = true;
    }

    if(tubeRadius < 0){
        oss << "Toric::_preToric: tube radius can not be negative" << std::endl
            << "\t given value is " << tubeRadius << std::endl;
        invalid = true;
    }

    if(invalid)
        throw std::invalid_argument(oss.str());
}

my::Toric::Toric(const float & pathRadius, const float &tubeRadius)
{
    _preToric(pathRadius, tubeRadius);

    _pathRadius = pathRadius;
    _tubeRadius = tubeRadius;
}

void my::Toric::_preOperatorCall(const float& pathAngle, const float& tubeAngle)
{
    std::ostringstream oss;

    if( !(0. <= pathAngle && pathAngle <= 2.*glm::pi<float>() && 0. <= tubeAngle && tubeAngle <= 2.*glm::pi<float>()) ){
        oss << "Spheric::Spheric::_preOperatorCall: Angles must be in radian and in range [0, 2pi]" << std::endl
            << "\t given pathAngle is " << pathAngle << std::endl
            << "\t given tubeAngle is " << tubeAngle << std::endl;
        throw std::invalid_argument(oss.str());
    }
}


my::Point my::Toric::operator()(const float & pathAngle, const float & tubeAngle) throw(std::invalid_argument)
{
    _preOperatorCall(pathAngle, tubeAngle);

    return my::Point((_pathRadius + _tubeRadius*std::cos(tubeAngle))*std::sin(pathAngle),
                     _tubeRadius*std::sin(tubeAngle),
                     (_pathRadius + _tubeRadius*std::cos(tubeAngle))*std::cos(pathAngle));
}
