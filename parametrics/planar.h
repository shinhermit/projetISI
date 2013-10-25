#ifndef PLANAR_H
#define PLANAR_H

#include "parametric.h"

namespace my{

class Planar : public Parametric
{
private:
    my::Point _A;
    my::Vector _u;
    my::Vector _v;

public:
    Planar(const my::Point & A, const my::Vector & u, const my::Vector & v);

    virtual Point operator()(const float&, const float&) throw(std::invalid_argument);
};

}

#endif // PLANAR_H
