#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <iostream>
#include "Object.hpp"

// Forward Declarations of used types. May delete later
class ExecutionContext;

/**
 * Superclass of all Expressions
 */
class Expression
{
public:
    enum ExpressionType {
        Unknown, Empty, Int, Float, String, Variable, Add,
        Subtract, Multiply, Divide, Assign, Sequence,
        Parenthesis, Bracket, Index, LogicalAnd, LogicalOr,
        LogicalXor, If, While, LessThan, LessThanOrEquals, 
        Equals, NotEquals, GreaterThanOrEquals, GreaterThan,
        LogicalNot, Try, CodeBlock
    };
    Expression( ExpressionType type );
    virtual ~Expression();
    virtual std::ostream& operator<<( std::ostream& os ) = 0;
    virtual Object* ToObject( ExecutionContext* context ) = 0;
    friend std::ostream& operator<<( std::ostream& os, Expression* exp );
    
    ExpressionType type_;
};

#endif