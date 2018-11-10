#include "LessThanExpression.hpp"
#include "BoolObject.hpp"

LessThanExpression::LessThanExpression( Expression* left, Expression* right )
    : Expression( LessThan )
    , left_( left )
    , right_( right )
{}
LessThanExpression::~LessThanExpression()
{
    delete left_;
    delete right_;
    left_ = nullptr;
    right_ = nullptr;
}
std::ostream& LessThanExpression::operator<<( std::ostream& os )
{
    os << "[LessThan: "; *left_ << os; os << ", "; *right_ << os; return os << "]";
}
Object* LessThanExpression::ToObject( ExecutionContext* context )
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
    BoolObject* ret = left->LessThan( right, context );
    left->Release();
    right->Release();
    return ret;
}
