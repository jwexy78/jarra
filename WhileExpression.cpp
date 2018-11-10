#include "WhileExpression.hpp"
#include "NoneObject.hpp"
#include "BoolObject.hpp"

WhileExpression::WhileExpression( Expression* condition, Expression* block )
    : Expression( While )
    , condition_( condition )
    , block_( block )
{}
WhileExpression::~WhileExpression()
{
    delete condition_;
    delete block_;
    condition_ = nullptr;
    block_ = nullptr;
}
std::ostream& WhileExpression::operator<<( std::ostream& os )
{
    os << "[While: "; *condition_ << os; os << ", "; *block_ << os; return os << "]";
}
Object* WhileExpression::ToObject( ExecutionContext* context )
{
    Object* condition = condition_->ToObject( context );
    if( !condition )
    {
        return nullptr;
    }
    condition = condition->Finalize();
    bool runBlock = condition->BoolValue();
    condition->Release();
    Object* toReturn = new NoneObject();
    while( runBlock )
    {
        // Perform the block code
        Object* block = block_->ToObject( context );
        if( !block )
        {
            return nullptr;
        }
        block = block->Finalize();
        toReturn->Release();
        toReturn = block;
        // Re-interpret the condition
        condition = condition_->ToObject( context );
        if( !condition )
        {
            return nullptr;
        }
        condition = condition->Finalize();
        runBlock = condition->BoolValue();
        condition->Release();
    }
    return toReturn;
}
