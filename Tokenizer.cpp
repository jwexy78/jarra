#include "Tokenizer.hpp"
#include "TypeTokenizer.hpp"


/**
 * Combines the content of tokens in 'tokens' between index 
 * 'start' and 'end' into a new token with type 'type'
 */
inline void TokenCombine( std::vector<Token>& tokens, int start, int end, Token::TokenType type )
{
    std::string content = "";
    for(int i = start; i <= end; ++i )
    {
        content = content + tokens[i];
    }
    tokens.erase( tokens.begin() + start, tokens.begin() + end + 1 );
    tokens.insert( tokens.begin() + start, Token( type, content ) );
}

/**
 * Replaces tokens between index 'start' and 'end' with 'replaceWith' in 'tokens'
 */
inline void TokenReplace( std::vector<Token>& tokens, int start, int end, Token replaceWith )
{
    tokens.erase( tokens.begin() + start, tokens.begin() + end + 1 );
    tokens.insert( tokens.begin() + start, replaceWith );
}

/**
 * Combine [Integer, ".", Integer] and [".", Integer] sequences
 * into single float tokens
 */
void CombineFloats( std::vector<Token>& tokens )
{
    for( int i = 0; i + 2 < tokens.size(); ++i )
    {
        if( tokens[i] == Token::Int &&
            tokens[i+1] == "." &&
            tokens[i+2] == Token::Int )
        {
            std::string content = tokens[i] + "." + tokens[i+2];
            TokenCombine( tokens, i, i+2, Token::Float );
        }
    }

    for( int i = 0; i + 1 < tokens.size(); ++i )
    {
        if( tokens[i] == "." &&
            tokens[i+1] == Token::Int )
        {
            std::string content = "." + tokens[i+1];
            TokenCombine( tokens, i, i+1, Token::Float );
        }
    }
}

/**
 * Combine all tokens between two quotes into a single
 * quoted string token
 */
void CombineQuotedStrings( std::vector<Token>& tokens )
{
    for( int openQuote = 0; openQuote < tokens.size(); ++openQuote )
    {
        if( tokens[openQuote] == "\"" )
        {
            std::string content = "";
            for( int closeQuote = openQuote + 1; closeQuote < tokens.size(); ++closeQuote )
            {
                if( tokens[closeQuote] == "\"" )
                {
                    TokenReplace( tokens, openQuote, closeQuote, Token( Token::QuotedString, content ) );
                    break;
                }
                else
                {
                    content = content + tokens[closeQuote];
                }
            }
        }
    }
}

/**
 * Combines operators of multiple characters into single operator tokens
 */
void CombineCompoundOperators( std::vector<Token>& tokens )
{
    // List of compound operators, in priority order.
    // For example, if '==' and '==>' are both operators, '==>' should
    // be first so that the '==' don't get combined first
    std::vector<std::string> compoundOperators = { "||", "&&", "==", "<=", ">=" };
    for( auto op = compoundOperators.begin(); op != compoundOperators.end(); ++op )
    {
        for( int i = 0; i + op->length() <= tokens.size(); ++i )
        {
            bool matches = true;
            for( int k = 0; k < op->length(); ++k )
            {
                if( tokens[i+k] != (*op)[k] )
                {
                    matches = false;
                    break;
                }
            }
            if( matches )
            {
                TokenCombine( tokens, i, i + op->length() - 1, Token::Operator );
            }
        }
    }
}

void CombineNegativeNumbers( std::vector<Token>& tokens )
{
    if( tokens.size() < 2 )
    {
        return;
    }
    
    if( tokens[0] == "-" && ( tokens[1] == Token::Int || tokens[1] == Token::Float ) )
    {
        TokenCombine( tokens, 0, 1, tokens[1].GetType() );
    }

    // Combine [Operator, "-", (Int/Float)] into [Operator, (Negative Num)]
    for( int i = 0; i + 2 < tokens.size(); ++i )
    {
        if( tokens[i] == Token::Operator && 
            tokens[i+1] == "-" &&
            (tokens[i+2] == Token::Int || tokens[i+2] == Token::Float) )
        {
            TokenCombine( tokens, i+1, i+2, tokens[i+2].GetType() );
        }
    }
}

/**
 * Tokenize a string into a list of Tokens
 */
std::vector<Token> Tokenizer::Tokenize( std::string content )
{
    std::vector<TypeToken> typeTokens = TypeTokenizer::TypeTokenize( content );
    std::vector<Token> tokens;
    for( int i = 0; i < typeTokens.size(); ++i )
    {
        tokens.push_back( Token( typeTokens[i] ) );
    }

    CombineFloats( tokens );
    CombineQuotedStrings( tokens );
    CombineCompoundOperators( tokens );
    CombineNegativeNumbers( tokens );

    return tokens;
}