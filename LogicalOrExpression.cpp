#include "LogicalOrExpression.hpp"
#include "BoolObject.hpp"

LogicalOrExpression::LogicalOrExpression( Expression* left, Expression* right )
    : Expression( Add )
    , left_( left )
    , right_( right )
{}
LogicalOrExpression::~LogicalOrExpression()
{
    delete left_;
    delete right_;
    left_ = nullptr;
    right_ = nullptr;
}
std::ostream& LogicalOrExpression::operator<<( std::ostream& os )
{
    os << "[LogicalOr: "; *left_ << os; os << ", "; *right_ << os; return os << "]";
}
Object* LogicalOrExpression::ToObject( ExecutionContext* context )
{
    Object* left = left_->ToObject( context );
    if( !left )
    {
        return nullptr;
    }
    left = left->Finalize();
    bool leftVal = left->BoolValue();
    left->Release();
    if( leftVal )
    {
        return new BoolObject( true );
    }
    Object* right = right_->ToObject( context );
    if( !right )
    {
        return nullptr;
    }
    right = right->Finalize();
    bool rightVal = right->BoolValue();
    right->Release();
    return new BoolObject( rightVal );
}
