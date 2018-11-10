#include "Token.hpp"

Token::Token( TokenType type, std::string content )
    : type_( type )
    , content_( content )
{
}

Token::Token( TypeToken typeToken )
    : content_( typeToken.content_ )
{
    switch( typeToken.type_ )
    {
        case TypeToken::Number:
            type_ = Int;
            break;
        case TypeToken::String:
            type_ = String;
            break;
        case TypeToken::Operator:
            type_ = Operator;
            break;
    }
}

bool Token::operator==( const TokenType& type ) const
{
    return type_ == type;
}

bool Token::operator==( const std::string& content ) const
{
    return content_ == content;
}

bool Token::operator==( const char& content ) const
{
    return content_.length() == 1 && content_[0] == content;
}

bool Token::operator!=( const char& content ) const
{
    return !(*this == content );
}

std::string Token::operator+( const std::string& content ) const
{
    return content_ + content;
}

std::string Token::operator+( const Token& token ) const
{
    return content_ + token.content_;
}

std::string operator+( std::string string, const Token& token )
{
    return string + token.content_;
}

std::ostream& operator<<( std::ostream& os, const Token& token )
{  
    os << "'" << token.content_ << "' (" << token.GetTypeAsString() << ")";
    return os;  
}

Token::TokenType Token::GetType()
{
    return type_;
}

std::string Token::GetContent()
{
    return content_;
}

std::string Token::GetTypeAsString() const
{
    switch( type_ )
    {
        case Int:
            return "Int";
        case Float:
            return "Float";
        case String:
            return "String";
        case QuotedString:
            return "Quoted String";
        case Operator:
            return "Operator";
    }
}