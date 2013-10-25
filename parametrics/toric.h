#ifndef TORIC_H
#define TORIC_H

#include "parametric.h"

namespace my{

class Toric : public Parametric
{
private:
    float _pathRadius;
    float _tubeRadius;

    void _preToric(const float & pathRadius, const float & tubeRadius);
    void _preOperatorCall(const float& pathAngle, const float& tubeAngle);

public:
    Toric(const float & pathRadius=0.6, const float & tubeRadius=0.4);

    Point operator()(const float& pathAngle, const float& tubeAngle) throw(std::invalid_argument);
};

}
#endif // TORIC_H
