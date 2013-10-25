#ifndef SPHERIC_H
#define SPHERIC_H

#include "parametric.h"

namespace my{

class Spheric : public Parametric
{
private:
    float _radius;

    void _preSpheric(const float &radius);
    void _preOperatorCall(const float& polar, const float& azimutal);

public:
    Spheric(const float &radius=1.);

    Point operator()(const float& polar, const float& azimutal) throw(std::invalid_argument);
};

}

#endif // SPHERIC_H
