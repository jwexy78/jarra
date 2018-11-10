#ifndef FUNCTION_OBJECT_HPP
#define FUNCTION_OBJECT_HPP

#include "Object.hpp"

class FunctionObject : public Object
{
public:
    FunctionObject();
    std::string ToString();
    bool BoolValue();
    virtual Object* Call( Object* parameter, ExecutionContext* context );
};

#endif