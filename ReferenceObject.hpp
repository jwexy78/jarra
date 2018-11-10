#ifndef REFERENCE_OBJECT_HPP
#define REFERENCE_OBJECT_HPP

#include "Object.hpp"

class ReferenceObject : public Object
{
public:
    ReferenceObject( Object** reference, Object* root );

    std::string ToString() override;
    bool BoolValue() override;
    Object* Assign( Object* other, ExecutionContext* context ) override;
    Object* Finalize( const ExecutionContext* ) override;
    void Destroy() override;

    Object** reference_;
    Object* root_;
};

#endif