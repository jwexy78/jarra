#include "MultiplyExpression.hpp"

MultiplyExpression::MultiplyExpression( Expression* left, Expression* right )
    : Expression( Multiply )
    , left_( left )
    , right_( right )
{}
MultiplyExpression::~MultiplyExpression()
{
    delete left_;
    delete right_;
    left_ = nullptr;
    right_ = nullptr;
}
std::ostream& MultiplyExpression::operator<<( std::ostream& os )
{
    os << "[Multiply: "; *left_ << os; os << ", "; *right_ << os; return os << "]";
}
Object* MultiplyExpression::ToObject( ExecutionContext* context )
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
    Object* ret = left->Multiply( right, context );
    left->Release();
    right->Release();
    return ret;
}
