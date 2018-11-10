#ifndef INDEX_EXPRESSION_HPP
#define INDEX_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class IndexExpression : public Expression
{
public:
    IndexExpression( Expression* caller, Expression* parameter );
    ~IndexExpression();
    std::ostream& operator<<( std::ostream& os );
    Object* ToObject( ExecutionContext* context );
protected:
    Expression* caller_;
    Expression* parameter_;
};

#endif