#ifndef REFERENCE_OBJECT_HPP
#define REFERENCE_OBJECT_HPP

#include "Object.hpp"

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

#endif