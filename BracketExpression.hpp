#ifndef BRACKET_EXPRESSION_HPP
#define BRACKET_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class BracketExpression : public Expression
{
public:
    BracketExpression( Expression* content );
    ~BracketExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* content_;
};

#endif