#include "UnknownExpression.hpp"

#include "AddExpression.hpp"
#include "AssignExpression.hpp"
#include "BracketExpression.hpp"
#include "CodeBlockExpression.hpp"
#include "DivideExpression.hpp"
#include "EmptyExpression.hpp"
#include "EqualsExpression.hpp"
#include "FloatExpression.hpp"
#include "FunctionExpression.hpp"
#include "IfExpression.hpp"
#include "IndexExpression.hpp"
#include "IntExpression.hpp"
#include "LessThanExpression.hpp"
#include "ListExpression.hpp"
#include "LogicalAndExpression.hpp"
#include "LogicalNotExpression.hpp"
#include "LogicalOrExpression.hpp"
#include "MultiplyExpression.hpp"
#include "ParenthesisExpression.hpp"
#include "SequenceExpression.hpp"
#include "StringExpression.hpp"
#include "SubtractExpression.hpp"
#include "TryExpression.hpp"
#include "VariableExpression.hpp"
#include "WhileExpression.hpp"

#include "StringObject.hpp"
#include "ExecutionContext.hpp"

bool TokenSplit( std::vector<Token>& tokens, Expression*& leftExpression, 
    Expression*& rightExpression, std::vector<std::string> splitStrings, 
    bool forward, std::string& match, std::string& error )
{
    int parens = 0;
    int brackets = 0;
    int braces = 0;
    int i = ( forward ? 0 : tokens.size() - 1 );
    for(; ( forward && i < tokens.size()) || ( !forward && i >= 0 ); forward ? ++i : --i )
    {
        if( tokens[i] == "(" )
        {
            parens++;
            continue;
        }
        else if( tokens[i] == ")" )
        {
            parens--;
            continue;
        }
        else if( tokens[i] == "[" )
        {
            brackets++;
            continue;
        }
        else if( tokens[i] == "]" )
        {
            brackets--;
            continue;
        }
        else if( tokens[i] == "{" )
        {
            braces++;
            continue;
        }
        else if( tokens[i] == "}" )
        {
            braces--;
            continue;
        }
        if( parens || brackets || braces )
        {
            continue;
        }
        for( int j = 0; j < splitStrings.size(); ++j )
        {
            if( tokens[i] == splitStrings[j] )
            {
                std::vector<Token> left( tokens.begin(), tokens.begin() + i );
                std::vector<Token> right( tokens.begin() + i + 1, tokens.end() );
                UnknownExpression uleft( left );
                UnknownExpression uright( right );
                // If both have errors, left's error will be returned
                rightExpression = uright.ToKnownExpression( error );
                leftExpression = uleft.ToKnownExpression( error );
                match = std::string("") + tokens[i];
                return true;
            }
        }
    }
    return false;
}

int FindMatching( std::vector<Token>& tokens, std::string symbol, int start, bool forward = true )
{
    int parens = 0;
    int braces = 0;
    int brackets = 0;
    int i = start;
    while( ( forward && i < tokens.size() )
        || ( !forward && i >= 0 ) )
    {
        if( !parens && !braces && !brackets )
        {
            if( tokens[i] == symbol )
            {
                return i;
            }
        }
        if( tokens[i] == "(" )
        {
            parens--;
        }
        else if( tokens[i] == ")" )
        {
            parens++;
        }
        else if( tokens[i] == "{" )
        {
            braces--;
        }
        else if( tokens[i] == "}" )
        {
            braces++;
        }
        else if( tokens[i] == "[" )
        {
            braces--;
        }
        else if( tokens[i] == "]" )
        {
            braces++;
        }
        if( forward )
        {
            i++;
        }
        else
        {
            i--;
        }
    }
    return -1;
}

int FindMatching( std::vector<Token>& tokens, std::string symbol )
{
    return FindMatching( tokens, symbol, tokens.size() - 2, false );
}

UnknownExpression::UnknownExpression( std::vector<Token> tokens )
    : Expression( Unknown )
    , tokens_( tokens )
{
}

/**
 * Converts an UnknownExpression to a KnownExpression
 * Always returns an Expression, representing the furthest the expresionizer
 * got in understanding the tokens
 * Sets 'errorMessage' to the error if an error occured
 */
Expression* UnknownExpression::ToKnownExpression( std::string& errorMessage )
{
    if( tokens_.size() == 0 )
    {
        return new EmptyExpression();
    }
    if( tokens_.size() == 1 )
    {
        Token token = tokens_[0];
        switch( token.GetType() )
        {
            case Token::Int:
                return new IntExpression( stoi( token.GetContent() ) );
            case Token::Float:
                return new FloatExpression( stof( token.GetContent() ) );
            case Token::QuotedString:
                return new StringExpression( token.GetContent() );
            case Token::String:
                return new VariableExpression( token.GetContent() );
            default:
                errorMessage = "Token '" + token.GetContent() + "' (of type " + token.GetTypeAsString() + ") is not a valid expression";
                return new UnknownExpression( tokens_ );
        }
    }

    Expression* left;
    Expression* right;

    std::string match;
    std::vector<std::string> s0 = {";"};
    if( TokenSplit( tokens_, left, right, s0, false, match, errorMessage ) )
    {
        return new SequenceExpression( left, right );
    }

    std::vector<std::string> s1_5 = {","};
    if( TokenSplit( tokens_, left, right, s1_5, false, match, errorMessage ) )
    {
        return new ListExpression( left, right );
    }

    std::vector<std::string> s1 = {"="};
    if( TokenSplit( tokens_, left, right, s1, true, match, errorMessage ) )
    {
        return new AssignExpression( left, right );
    }

    std::vector<std::string> s4 = {"||"};
    if( TokenSplit( tokens_, left, right, s4, false, match, errorMessage ) )
    {
        return new LogicalOrExpression( left, right );
    }
    std::vector<std::string> s5 = {"&&"};
    if( TokenSplit( tokens_, left, right, s5, false, match, errorMessage ) )
    {
        return new LogicalAndExpression( left, right );
    }

    std::vector<std::string> s5_5 = { "<", "<=", "==", "!=", ">=", ">"};
    if( TokenSplit( tokens_, left, right, s5_5, false, match, errorMessage ) )
    {
        if( match == "<" )
            return new LessThanExpression( left, right );
        if( match == "==" )
            return new EqualsExpression( left, right );
    }
    
    std::vector<std::string> s2 = {"+","-"};
    if( TokenSplit( tokens_, left, right, s2, false, match, errorMessage ) )
    {
        if( match == "+" )
        {
            return new AddExpression( left, right );
        }
        else
        {
            return new SubtractExpression( left, right );
        }
    }
    std::vector<std::string> s3 = {"*","/"};
    if( TokenSplit( tokens_, left, right, s3, false, match, errorMessage ) )
    {
        if( match == "*" )
        {
            return new MultiplyExpression( left, right );
        }
        else
        {
            return new DivideExpression( left, right );
        }
    }

    if( tokens_[0] == "!" )
    {
        std::vector<Token> subtokens( tokens_.begin() + 1, tokens_.begin() + tokens_.size() );
        UnknownExpression subexpression( subtokens );
        Expression* subexpr = subexpression.ToKnownExpression( errorMessage );
        return new LogicalNotExpression( subexpr );
    }

    if( tokens_[tokens_.size() - 1] == ")" )
    {
        int i = FindMatching( tokens_, "(" );
        if( i == 0 )
        {
            // Matched '(' was at the start of the expression,
            // so it is a parenthesis expression
            tokens_.erase( tokens_.begin() + (tokens_.size() - 1) );
            tokens_.erase( tokens_.begin() );
            return new ParenthesisExpression( ToKnownExpression( errorMessage ) );
        }
        else if( i > 0 )
        {
            // Otherwise, it is a function call
            std::vector<Token> leftTokens( tokens_.begin(), tokens_.begin() + i );
            std::vector<Token> rightTokens( tokens_.begin() + i + 1, tokens_.end() - 1 );
            UnknownExpression callerExpression( leftTokens );
            UnknownExpression parameterExpresssion( rightTokens );
            Expression* parameter = parameterExpresssion.ToKnownExpression( errorMessage );
            Expression* caller = callerExpression.ToKnownExpression( errorMessage );
            return new FunctionExpression( caller, parameter );
        }
    }

    if( tokens_[tokens_.size() - 1] == "]" )
    {
        int i = FindMatching( tokens_, "[" );
        if( i == 0 )
        {
            // Matched '[' was at the start of the expression,
            // so it is a bracket expression
            tokens_.erase( tokens_.begin() + (tokens_.size() - 1) );
            tokens_.erase( tokens_.begin() );
            return new BracketExpression( ToKnownExpression( errorMessage ) );
        }
        else if( i > 0 )
        {
            // Otherwise, it is an index
            std::vector<Token> leftTokens( tokens_.begin(), tokens_.begin() + i );
            std::vector<Token> rightTokens( tokens_.begin() + i + 1, tokens_.end() - 1 );
            UnknownExpression callerExpression( leftTokens );
            UnknownExpression parameterExpresssion( rightTokens );
            Expression* parameter = parameterExpresssion.ToKnownExpression( errorMessage );
            Expression* caller = callerExpression.ToKnownExpression( errorMessage );
            return new IndexExpression( caller, parameter );
        }
    }

    if( tokens_[tokens_.size() - 1] == "}" )
    {
        int i = FindMatching( tokens_, "{", tokens_.size() - 2, false );
        if( i > 0 )
        {
            std::vector<Token> conditionTokens( tokens_.begin() + 1, tokens_.begin() + i );
            std::vector<Token> blockTokens( tokens_.begin() + i + 1, tokens_.end() - 1 );
            UnknownExpression conditionExpression( conditionTokens );
            UnknownExpression blockExpression( blockTokens );
            Expression* condition = conditionExpression.ToKnownExpression( errorMessage );
            Expression* block = blockExpression.ToKnownExpression( errorMessage );
            if( tokens_[0] == "if" )
            {
                return new IfExpression( condition, block );
            }
            if( tokens_[0] == "while" )
            {
                return new WhileExpression( condition, block );
            }
            if( tokens_[0] == "try" )
            {
                return new TryExpression( condition, block );
            }
        }
        else if( i == 0 )
        {
            tokens_.erase( tokens_.begin() + (tokens_.size() - 1) );
            tokens_.erase( tokens_.begin() );
            return new CodeBlockExpression( ToKnownExpression( errorMessage ) );
        }
    }

    std::stringstream ss;
    ss << "Could Not Understand: "; *this << ss;

    errorMessage = ss.str();
    return new UnknownExpression( *this );
}

Object* UnknownExpression::ToObject( ExecutionContext* context )
{
    context->SetException( new StringObject( "Attempted to translate unknown expression into object" ) );
    return nullptr;
}

std::ostream& UnknownExpression::operator<<( std::ostream& os )
{
    os << "[Unknown Expression: ";
    for( auto i = tokens_.begin(); i != tokens_.end(); ++i )
    {
        os << (*i) << ",";
    }
    os << "]";
    return os;
}

std::stringstream& UnknownExpression::operator<<( std::stringstream& os )
{
    os << "[Unknown Expression: ";
    for( auto i = tokens_.begin(); i != tokens_.end(); ++i )
    {
        os << (*i) << ",";
    }
    os << "]";
    return os;
}

