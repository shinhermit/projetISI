#ifndef FUNCEXPCOS_H
#define FUNCEXPCOS_H

#include "functional.h"

namespace my{

class FuncExpCos: public Functional
{
public:
    FuncExpCos();

    float operator()(const float& x, const float& y)const throw(std::invalid_argument);
};

}

#endif // FUNCEXPCOS_H
