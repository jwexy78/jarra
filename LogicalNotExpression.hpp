#ifndef LOGICALNOT_EXPRESSION_HPP
#define LOGICALNOT_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class LogicalNotExpression : public Expression
{
public:
    LogicalNotExpression( Expression* content );
    ~LogicalNotExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* content_;
};

#endif