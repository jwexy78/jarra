#include "LogicalAndExpression.hpp"
#include "BoolObject.hpp"

LogicalAndExpression::LogicalAndExpression( Expression* left, Expression* right )
    : Expression( Add )
    , left_( left )
    , right_( right )
{}
LogicalAndExpression::~LogicalAndExpression()
{
    delete left_;
    delete right_;
    left_ = nullptr;
    right_ = nullptr;
}
std::ostream& LogicalAndExpression::operator<<( std::ostream& os )
{
    os << "[LogicalAnd: "; *left_ << os; os << ", "; *right_ << os; return os << "]";
}
Object* LogicalAndExpression::ToObject( ExecutionContext* context )
{
    Object* left = left_->ToObject( context );
    if( !left )
    {
        return nullptr;
    }
    left = left->Finalize();
    bool leftVal = left->BoolValue();
    left->Release();
    if( !leftVal )
    {
        return new BoolObject( false );
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
