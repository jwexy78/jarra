#ifndef TYPE_TOKENIZER_HPP
#define TYPE_TOKENIZER_HPP

#include <vector>
#include "TypeToken.hpp"

class TypeTokenizer
{
public:
    /**
     * Splits a string into a list of three types of tokens:
     * Numbers, Strings and Single-Character Operators
     */
    static std::vector<TypeToken> TypeTokenize( std::string content );
};

#endif