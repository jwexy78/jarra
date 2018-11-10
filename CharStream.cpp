#include "CharStream.hpp"

CharStream::CharStream( std::string content )
    : content_( content )
    , index_ ( 0 )
{
}

char CharStream::Next()
{
    if( index_ >= content_.length() )
    {
        return (char)0;
    }
    return content_[index_++];
}

void CharStream::Back()
{
    if( index_ > 0 )
    {
        index_--;
    }
}