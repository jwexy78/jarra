#include "TypeTokenizer.hpp"
#include "CharStream.hpp"

/**
 * Checks if a character is a number, ie: 0,1, ... 8,9
 */
inline bool IsNumber( char c )
{
    return c >= '0' && c <= '9';
}

/**
 * Checks if a character is a letter, ie: a,b ... y,z,A,B ... Y,Z
 */
inline bool IsLetter( char c )
{
    return ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' );
}


std::vector<TypeToken> TypeTokenizer::TypeTokenize( std::string content )
{
    std::vector<TypeToken> tokens;
    CharStream chars( content );
    std::string curr;
    TypeToken::TokenType currType;
    char c;
    while( ( c = chars.Next() ) )
    {
        if( !curr.length() )
        {
            if( IsNumber( c ) )
            {
                currType = TypeToken::Number;
                curr += c;
            }
            else if( IsLetter( c ) )
            {
                currType = TypeToken::String;
                curr += c;
            }
            else
            {
                currType = TypeToken::Operator;
                tokens.push_back( TypeToken( TypeToken::Operator, c ) );
            }
        }
        else
        {
            switch( currType )
            {
                case TypeToken::Number:
                {
                    if( IsNumber( c ) )
                    {
                        curr += c;
                    }
                    else
                    {
                        tokens.push_back( TypeToken( TypeToken::Number, curr ) );
                        curr = "";
                        chars.Back();
                    }
                    break;
                }
                case TypeToken::String:
                {
                    if( IsNumber( c ) || IsLetter( c ) )
                    {
                        curr += c;
                    }
                    else
                    {
                        tokens.push_back( TypeToken( TypeToken::String, curr ) );
                        curr = "";
                        chars.Back();
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
    if( curr.length() )
    {
        tokens.push_back( TypeToken( currType, curr ) );
    }
    return tokens;
}