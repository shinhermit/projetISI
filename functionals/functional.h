#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <stdexcept>
#include <glm/gtx/constants.hpp>

namespace my{

class Functional
{
public:
    Functional();
    virtual ~Functional();

    //throw(std::invalid_argument) ensures the function's domain
    virtual float operator()(const float&, const float&)const throw(std::invalid_argument) =0;
};

}

#endif // FUNCTIONAL_H
