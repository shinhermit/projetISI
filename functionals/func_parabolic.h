#ifndef PARABOLIC_H
#define PARABOLIC_H

#include "functional.h"

namespace my{

/**
 * An implementation of my::Functional, a 2-parameters mathematical function objects
 *
 */
class FuncParabolic: public Functional
{
public:
    FuncParabolic();

    /**
     * An implementation of my::Functional::operator()
     */
    float operator()(const float & x, const float & y)const throw(std::invalid_argument);
};

}

#endif // PARABOLIC_H
