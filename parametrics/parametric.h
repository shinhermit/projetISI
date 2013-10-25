#ifndef PARAMETRIC_H
#define PARAMETRIC_H

#include <stdexcept>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtx/constants.hpp>
#include "../my_types.h"
#include "utils/constant.h"

namespace my{

class Parametric
{
public:
    Parametric();
    virtual ~Parametric();

    virtual Point operator()(const float&, const float&) throw(std::invalid_argument) =0;
};

}

#endif // PARAMETRIC_H
