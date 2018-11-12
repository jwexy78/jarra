#ifndef CODEBLOCK_EXPRESSION_HPP
#define CODEBLOCK_EXPRESSION_HPP

#include "Expression.hpp"
#include "Object.hpp"

class CodeBlockExpression : public Expression
{
public:
    CodeBlockExpression( Expression* content );
    ~CodeBlockExpression();
    std::ostream& operator<<( std::ostream& os ) override;
    Object* ToObject( ExecutionContext* context ) override;
    
protected:
    Expression* content_;
};

#endif