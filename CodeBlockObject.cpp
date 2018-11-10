#include "CodeBlockObject.hpp"

CodeBlockObject::CodeBlockObject( Expression* block )
    : Object( Object::CodeBlock )
    , block_( block )
{
}

std::string CodeBlockObject::ToString()
{
    return "CodeBlock";
}

bool CodeBlockObject::BoolValue()
{
    return true;
}

Object* CodeBlockObject::Call( Object* parameter, ExecutionContext* context )
{
    return block_->ToObject( context );
}