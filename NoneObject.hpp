#ifndef NONE_OBJECT_HPP
#define NONE_OBJECT_HPP

#include "Object.hpp"

class NoneObject : public Object
{
public:
    NoneObject();
    std::string ToString() override;
    bool BoolValue() override;
    BoolObject* Equals( Object* other, ExecutionContext* context ) override;
};

#endif