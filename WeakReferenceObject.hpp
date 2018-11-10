#ifndef WEAK_REFERENCE_OBJECT_HPP
#define WEAK_REFERENCE_OBJECT_HPP

#include "Object.hpp"
#include <unordered_map>

class WeakReferenceObject : public Object
{
public:
    WeakReferenceObject( std::unordered_map<std::string,Object*>* variables, std::string name, Object* root );

    std::string ToString();
    bool BoolValue();
    Object* Assign( Object* other, ExecutionContext* context );
    Object* Finalize();
    void Destroy();

    std::unordered_map<std::string,Object*>* reference_;
    std::string name_;
    Object* root_;
};

#endif
