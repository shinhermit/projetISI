#include "conic.h"

void my::Conic::_preInit(const float & aperture) throw(std::invalid_argument)
{
    std::ostringstream oss;

    if( !(0. < aperture < 180.) ){
        oss << "Conic::operator(): The aperture angle is given in degree (for commodity reasons), in range ]0,180[" << std::endl
            << "\t given value is " << aperture <<std::endl;
        throw std::invalid_argument(oss.str());
    }
}

void my::Conic::_init(const float & aperture)
{
    _preInit(aperture);

    _aperture = aperture*glm::pi<float>() / 180.;
}

my::Conic::Conic(const my::Point & center, const float & aperture) throw(std::invalid_argument)
    :_center(center)
{
    _init(aperture);
}

my::Conic::Conic(const float & aperture) throw(std::invalid_argument)
    :_center(Point(0,0,0))
{
    _init(aperture);
}

my::Point my::Conic::operator()( const float& z, const float& azimut) throw(std::invalid_argument)
{
    if( !(0. <= azimut <= 2.*glm::pi<float>()) )
        throw std::invalid_argument("Conic::operator(): Angles must be in radian and in range [0, 2pi]");

    return my::Point(std::abs(z)*std::tan(_aperture)*std::sin(azimut),
                     z,
                     std::abs(z)*std::tan(_aperture)*std::cos(azimut)) + _center;
}
