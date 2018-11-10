#ifndef FLOAT_OBJECT_HPP
#define FLOAT_OBJECT_HPP

#include "Object.hpp"

class FloatObject : public Object
{
public:
    FloatObject( float data );
    std::string ToString() override;
    bool BoolValue() override;
    Object* Add( Object* other, ExecutionContext* context ) override;
    Object* Subtract( Object* other, ExecutionContext* context ) override;
    Object* Multiply( Object* other, ExecutionContext* context ) override;
    Object* Divide( Object* other, ExecutionContext* context ) override;
    BoolObject* Equals( Object* other, ExecutionContext* context ) override;

    float data_;
};

#endif