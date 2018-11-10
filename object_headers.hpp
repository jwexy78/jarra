/**
 * Holds the .h contents for all Object types
 * Any functions needed to manipulate an object should be
 * forward-declared here
 */

#ifndef OBJECT_HEADERS_H_
#define OBJECT_HEADERS_H_

#include "execution_context.hpp"

class BoolObject;

class Object
{
public:
    enum ObjectType { None, Int, Float, String, Function, List, Reference, Bool };

    static std::string TypeToString( ObjectType type );

    Object( ObjectType type );
    virtual ~Object();

    // Functions that all Objects must implement
    virtual std::string ToString() = 0;
    virtual bool BoolValue() = 0;

    // Functions that all Objects may implement
    virtual Object* Add( Object* other, ExecutionContext* context );
    virtual Object* Subtract( Object* other, ExecutionContext* context );
    virtual Object* Multiply( Object* other, ExecutionContext* context );
    virtual Object* Divide( Object* other, ExecutionContext* context );
    virtual Object* Assign( Object* other, ExecutionContext* context );
    virtual Object* Call( Object* parameter, ExecutionContext* context );
    virtual Object* Join( Object* other, ExecutionContext* context );
    virtual Object* Index( Object* other, ExecutionContext* context );
    virtual Object* Finalize();
    virtual BoolObject* LessThan( Object* other, ExecutionContext* context );
    virtual BoolObject* Equals( Object* other, ExecutionContext* context );
/*
    virtual Object* BinaryOr( Object* other, ExecutionContext* context );
    virtual Object* BinaryOr( Object* other, ExecutionContext* context );
*/

    Object* ThrowNotImplemented( std::string operation, ObjectType otherType, ExecutionContext* context );

    Object* ThrowAddNotImplemented( ObjectType otherType, ExecutionContext* context );
    Object* ThrowSubtractNotImplemented( ObjectType otherType, ExecutionContext* context );
    Object* ThrowMultiplyNotImplemented( ObjectType otherType, ExecutionContext* context );
    Object* ThrowDivideNotImplemented( ObjectType otherType, ExecutionContext* context );
    Object* ThrowAssignNotImplemented( ObjectType otherType, ExecutionContext* context );
    Object* ThrowCallNotImplemented( ObjectType otherType, ExecutionContext* context );
    Object* ThrowJoinNotImplemented( ObjectType otherType, ExecutionContext* context );
    Object* ThrowIndexNotImplemented( ObjectType otherType, ExecutionContext* context );
    Object* ThrowEqualsNotImplemented( ObjectType otherType, ExecutionContext* context );
    Object* ThrowLessThanNotImplemented( ObjectType otherType, ExecutionContext* context );
    // The Type of the object, from the ObjectType enum above
    ObjectType type_;

    void Acquire();
    bool Release();
    virtual void Destroy();
protected:
    int referenceCount_;
};











class ReferenceObject : public Object
{
public:
    ReferenceObject( Object** reference, Object* root );

    std::string ToString();
    bool BoolValue();
    Object* Assign( Object* other, ExecutionContext* context );
    Object* Finalize();
    void Destroy();

    Object** reference_;
    Object* root_;
};


class CodeBlockObject : public Object
{
public:
    CodeBlockObject( Expression* expression );

    std::string ToString();
    Object* Call( Object* parameter, ExecutionContext* context );

    Expression* expression_;
};

#endif