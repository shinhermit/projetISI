#ifndef PLANAREXPRESSION_H
#define PLANAREXPRESSION_H

#include "my_types.h"

namespace my{

class PlanarExpression
{
private:
    float _a;
    float _b;
    float _c;
    float _d;

public:
    PlanarExpression(const my::Point & A, const my::Vector & u, const my::Vector & v);

    float operator()(const float & x, const float & y, const float & z)const;
    float operator()(const my::Point & P)const;
};

}
#endif // PLANAREXPRESSION_H
