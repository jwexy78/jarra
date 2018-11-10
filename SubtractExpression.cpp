#include "SubtractExpression.hpp"

SubtractExpression::SubtractExpression( Expression* left, Expression* right )
    : Expression( Subtract )
    , left_( left )
    , right_( right )
{}
SubtractExpression::~SubtractExpression()
{
    delete left_;
    delete right_;
    left_ = nullptr;
    right_ = nullptr;
}
std::ostream& SubtractExpression::operator<<( std::ostream& os )
{
    os << "[Subtract: "; *left_ << os; os << ", "; *right_ << os; return os << "]";
}
Object* SubtractExpression::ToObject( ExecutionContext* context )
{
    Object* left = left_->ToObject( context );
    if( !left ) return nullptr;
    Object* right = right_->ToObject( context );
    if( !right )
    {
        left->Release();
        return nullptr;
    }
    left = left->Finalize();
    right = right->Finalize();
    Object* ret = left->Subtract( right, context );
    left->Release();
    right->Release();
    return ret;
}
