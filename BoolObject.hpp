#ifndef BOOL_OBJECT_HPP
#define BOOL_OBJECT_HPP

#include "Object.hpp"

class BoolObject : public Object
{
public:
    BoolObject( bool value );
    std::string ToString();
    bool BoolValue();

    bool value_;
};

#endif