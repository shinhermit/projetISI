/**
 * @file   functional.h
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * @brief  Represents a mathematical (non-discrete) sin cos function
 *
 *
 */
#ifndef FUNCEXPCOS_H
#define FUNCEXPCOS_H

#include "functional.h"

namespace my{

/**
 * An implementation of my::Functional, a 2-parameters mathematical function objects
 *
 */
class FuncExpCos: public Functional
{
public:
    FuncExpCos();

    /**
     * An implementation of my::Functional::operator()
     */
    float operator()(const float & x, const float & y)const throw(std::invalid_argument);
};

}

#endif // FUNCEXPCOS_H
