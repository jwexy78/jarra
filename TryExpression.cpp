#include "TryExpression.hpp"
#include "ExecutionContext.hpp"

TryExpression::TryExpression( Expression* condition, Expression* block )
    : Expression( Try )
    , condition_( condition )
    , block_( block )
{}
TryExpression::~TryExpression()
{
    delete condition_;
    delete block_;
    condition_ = nullptr;
    block_ = nullptr;
}
std::ostream& TryExpression::operator<<( std::ostream& os )
{
    os << "[Try: "; *condition_ << os; os << ", "; *block_ << os; return os << "]";
}
Object* TryExpression::ToObject( ExecutionContext* context )
{
    Object* condition = condition_->ToObject( context );
    if( !condition )
    {
        // If execution of the condition failed
        context->ClearException();
        Object* block = block_->ToObject( context );
        if( !block )
        {
            return nullptr;
        }
        block = block->Finalize( context );
        return block;
    }
    else
    {
        condition = condition->Finalize( context );
        return condition;
    }
}
