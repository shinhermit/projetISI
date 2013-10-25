#ifndef FUNCSINCOS_H
#define FUNCSINCOS_H

#include "functional.h"

namespace my{

class FuncSinCos: public Functional
{
public:
    FuncSinCos();

    float operator()(const float& x, const float& y)const throw(std::invalid_argument);
};

}

#endif // FUNCSINCOS_H
