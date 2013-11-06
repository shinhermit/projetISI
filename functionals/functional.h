/**
 * @file   functional.h
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * @brief  Represents a mathematical (non-discrete) function
 *
 *
 */
#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <stdexcept>
#include <glm/gtx/constants.hpp>

namespace my{

/**
 * Abstract base classe for all 2-parameters mathematical function objects
 *
 */
class Functional
{
public:
    Functional();
    virtual ~Functional();

    /**
     * perform a mathematical calculus on it's two arguments and provides a result.
     *  Typicaly, operates on x and y, and results in z.
     * The throw clause ensures the function's domain
     */
    virtual float operator()(const float&, const float&)const throw(std::invalid_argument) =0;
};

}

#endif // FUNCTIONAL_H
