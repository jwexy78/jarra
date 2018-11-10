#ifndef LOGICALOR_EXPRESSION_HPP
#define LOGICALOR_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class LogicalOrExpression : public Expression
{
public:
    LogicalOrExpression( Expression* left, Expression* right );
    ~LogicalOrExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* left_;
    Expression* right_;
};

#endif