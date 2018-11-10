#ifndef LOGICALAND_EXPRESSION_HPP
#define LOGICALAND_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class LogicalAndExpression : public Expression
{
public:
    LogicalAndExpression( Expression* left, Expression* right );
    ~LogicalAndExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* left_;
    Expression* right_;
};

#endif