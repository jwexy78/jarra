#ifndef INT_OBJECT_HPP
#define INT_OBJECT_HPP

#include "Object.hpp"

class IntObject : public Object
{
public:
    IntObject( int data );
    std::string ToString() override;
    bool BoolValue() override;
    Object* Add( Object* other, ExecutionContext* context ) override;
    Object* Subtract( Object* other, ExecutionContext* context ) override;
    Object* Multiply( Object* other, ExecutionContext* context ) override;
    Object* Divide( Object* other, ExecutionContext* context ) override;
    BoolObject* LessThan( Object* other, ExecutionContext* context ) override;
    BoolObject* Equals( Object* other, ExecutionContext* context ) override;
    int data_;
};

#endif