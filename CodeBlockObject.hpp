#ifndef CODE_BLOCK_OBJECT_HPP
#define CODE_BLOCK_OBJECT_HPP

#include "Object.hpp"
#include "Expression.hpp"

class CodeBlockObject : public Object
{
public:
    CodeBlockObject( Expression* block );
    std::string ToString();
    bool BoolValue();

    Object* Call( Object* parameter, ExecutionContext* context );
protected:
    Expression* block_;
};

#endif