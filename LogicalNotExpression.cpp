#include "LogicalNotExpression.hpp"
#include "BoolObject.hpp"

LogicalNotExpression::LogicalNotExpression( Expression* content )
    : Expression( LogicalNot )
    , content_( content )
{}
LogicalNotExpression::~LogicalNotExpression()
{
    delete content_;
    content_ = nullptr;
}
std::ostream& LogicalNotExpression::operator<<( std::ostream& os )
{
    os << "[LogicalNot: "; *content_ << os; return os << "]";
}
Object* LogicalNotExpression::ToObject( ExecutionContext* context )
{
    Object* obj = content_->ToObject( context );
    if( !obj )
    {
        return nullptr;
    }
    obj = obj->Finalize( context );
    bool boolValue = obj->BoolValue();
    return new BoolObject( !boolValue );
}
