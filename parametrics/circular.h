#ifndef CIRCULAR_H
#define CIRCULAR_H

#include <iostream>
#include <sstream>

#include "parametric.h"

namespace my{

class Circular: public Parametric
{
private:
    float _radius;
    my::Point _center;

    void _preCircular(const float & radius);
    void _preOperatorCall(const float & distance, const float & azimut) throw(std::invalid_argument);

public:
    Circular(const float & radius=1., const my::Point & center=my::Point(0,0,0));

    Point operator()(const float & distance, const float & azimut) throw(std::invalid_argument);
};

}

#endif // CIRCULAR_H
