/**
 * @file   functional.h
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * @brief  Represents a mathematical (non-discrete) sin cos function
 *
 *
 */
#ifndef FUNCSINCOS_H
#define FUNCSINCOS_H

#include "functional.h"

namespace my{

/**
 * An implementation of my::Functional, a 2-parameters mathematical function objects
 *
 */
class FuncSinCos: public Functional
{
public:
    FuncSinCos();

    /**
     * An implementation of my::Functional::operator()
     */
    float operator()(const float & x, const float & y)const throw(std::invalid_argument);
};

}

#endif // FUNCSINCOS_H
