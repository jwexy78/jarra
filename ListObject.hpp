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
    std::string ToString() override;
    bool BoolValue() override;
    Object* Join( Object* other, ExecutionContext* context ) override;
    void Append( Object* other );
    Object* Index( Object* other, ExecutionContext* context ) override;
    void Destroy() override;
    ListObject* Finalize( const ExecutionContext* ) override;

    std::vector<Object*> contents_;
    bool finalized_;
};

#endif