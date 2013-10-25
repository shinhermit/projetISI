#ifndef CONIC_H
#define CONIC_H

#include "parametric.h"

namespace my{

class Conic: public Parametric
{
private:
    float _aperture;
    my::Point _center;

    void _preInit(const float & aperture) throw(std::invalid_argument);
    void _init(const float & aperture);

public:
    Conic(const my::Point & center, const float & aperture=26.5) throw(std::invalid_argument);
    Conic(const float & aperture=26.5) throw(std::invalid_argument);

    Point operator()(const float& z, const float& azimut) throw(std::invalid_argument);
};

}
#endif // CONIC_H
