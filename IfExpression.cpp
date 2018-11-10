#include "IfExpression.hpp"
#include "NoneObject.hpp"

IfExpression::IfExpression( Expression* condition, Expression* block )
    : Expression( If )
    , condition_( condition )
    , block_( block )
{}
IfExpression::~IfExpression()
{
    delete condition_;
    delete block_;
    condition_ = nullptr;
    block_ = nullptr;
}
std::ostream& IfExpression::operator<<( std::ostream& os )
{
    os << "[If: "; *condition_ << os; os << ", "; *block_ << os; return os << "]";
}
Object* IfExpression::ToObject( ExecutionContext* context )
{
    Object* condition = condition_->ToObject( context );
    if( !condition )
    {
        return nullptr;
    }
    condition = condition->Finalize( context );
    bool runBlock = condition->BoolValue();
    condition->Release();
    if( runBlock )
    {
        Object* block = block_->ToObject( context );
        if( !block )
        {
            return nullptr;
        }
        block = block->Finalize( context );
        return block;
    }
    return new NoneObject();
}
