#ifndef LIST_OBJECT_HPP
#define LIST_OBJECT_HPP

#include "Object.hpp"
#include <vector>

class ListObject : public Object
{
public:
    ListObject();
    ListObject( Object* left, Object* right );
    ListObject( ListObject* other );
    std::string ToString();
    bool BoolValue();
    Object* Join( Object* other, ExecutionContext* context );
    void Append( Object* other );
    Object* Index( Object* other, ExecutionContext* context );
    void Destroy();
    ListObject* Finalize();

    std::vector<Object*> contents_;
    bool finalized_;
};

#endif