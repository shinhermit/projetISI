#include "functional.h"

using namespace my;

Functional::Functional(const std::string & funcName)
    :_name(funcName)
{}

Functional::~Functional(){}

std::string Functional::name() const
{
    return _name;
}
