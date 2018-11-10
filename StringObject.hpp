#ifndef STRING_OBJECT_HPP
#define STRING_OBJECT_HPP

#include "Object.hpp"

class StringObject : public Object
{
public:
    StringObject( std::string content );
    std::string ToString() override;
    bool BoolValue() override;
    Object* Add( Object* other, ExecutionContext* context ) override;
    Object* Multiply( Object* other, ExecutionContext* context ) override;
    BoolObject* Equals( Object* other, ExecutionContext* context ) override;
    Object* Index( Object* other, ExecutionContext* context ) override;

    std::string data_;
};

#endif