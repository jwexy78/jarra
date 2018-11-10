#ifndef PARENTHESIS_EXPRESSION_HPP
#define PARENTHESIS_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class ParenthesisExpression : public Expression
{
public:
    ParenthesisExpression( Expression* content );
    ~ParenthesisExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* content_;
};

#endif