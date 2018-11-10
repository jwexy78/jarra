#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>

class BoolObject;
class ExecutionContext;

class Object
{
public:
    // The types an object can be
    enum ObjectType { None, Bool, Int, Float, String, List, Function, Reference, WeakReference,  CodeBlock };

    /**
     * Converts an object type into a human-readable string
     */
    static std::string TypeToString( ObjectType type );

    /**
     * Creates a new object of a certain type
     */
    Object( ObjectType type );
    virtual ~Object();

    // Functions that subclass Objects must implement //

    /**
     * Converts the object into a string
     */
    virtual std::string ToString() = 0;

    /**
     * Gets the 'Truthiness' value of an object
     */
    virtual bool BoolValue() = 0;

    // Functions that subclass Objects may implement //

    /**
     * Create a new object by adding another object to this object
     */
    virtual Object* Add( Object* other, ExecutionContext* context );

    /**
     * Create a new object by subtracting another object to this object
     */
    virtual Object* Subtract( Object* other, ExecutionContext* context );

    /**
     * Create a new object by multiplying another object to this object
     */
    virtual Object* Multiply( Object* other, ExecutionContext* context );

    /**
     * Create a new object by dividing another object to this object
     */
    virtual Object* Divide( Object* other, ExecutionContext* context );

    /**
     * Create a new object by assigning another object to this object
     */
    virtual Object* Assign( Object* other, ExecutionContext* context );

    /**
     * Create a new object by calling this object as a function with another object
     * as the parameter
     */
    virtual Object* Call( Object* parameter, ExecutionContext* context );

    /**
     * Create a new object by joining (list-concatenation) another object to this object
     */
    virtual Object* Join( Object* other, ExecutionContext* context );

    /**
     * Create a new object by indexing (ie: element at the the nth index)
     * with another object as the index value
     */
    virtual Object* Index( Object* other, ExecutionContext* context );

    /**
     * Create a new BoolObject by comparing via less-than another object and this object
     */
    virtual BoolObject* LessThan( Object* other, ExecutionContext* context );
    /**
     * Create a new BoolObject by comparing via equality another object and this object
     */
    virtual BoolObject* Equals( Object* other, ExecutionContext* context );

    /**
     * Finalizes the Object, turning it from some sort of non-directly usable reference
     * to a direct object
     */
    virtual Object* Finalize();

    // Helper-Functions to throw with an 
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

    /**
     * Acquire the object, increasing the reference count
     */
    void Acquire();

    /**
     * Releasing a reference to the Object, decreasing the reference
     * count and possibly freeing the object
     */
    bool Release();

    /**
     * Destroys the object when reference count is zero.
     * Subclasses should use this to Release any references to other
     * objects upon being freed
     */
    virtual void Destroy();

protected:
    int referenceCount_;
};

#endif