#ifndef CYLINDRIC_H
#define CYLINDRIC_H

#include "parametric.h"

namespace my{

class Cylindric : public Parametric
{
private:
    float _radius;
    my::Point _center;

    void _preCylindric(const float & radius);
    void _preOperatorCall(const float & alpha);

public:
    Cylindric(const float & radius=1., const my::Point & center=my::Point(0,0,0));

    Point operator()(const float & z, const float & alpha) throw(std::invalid_argument);
};

}
#endif // CYLINDRIC_H
