#ifndef WEAK_REFERENCE_OBJECT_HPP
#define WEAK_REFERENCE_OBJECT_HPP

#include "Object.hpp"
#include <unordered_map>

class WeakReferenceObject : public Object
{
public:
    WeakReferenceObject( int scope, std::string name, Object* root );

    std::string ToString() override;
    bool BoolValue() override;
    Object* Assign( Object* other, ExecutionContext* context ) override;
    Object* Finalize( const ExecutionContext* context ) override;
    void Destroy() override;

    int scope_;
    std::string name_;
    Object* root_;
};

#endif
