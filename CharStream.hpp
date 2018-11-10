#ifndef CHAR_STREAM_HPP
#define CHAR_STREAM_HPP

#include <string>
#include <iostream>

/**
 * A class that turns a string into a 'one char at a time' stream
 */
class CharStream
{
public:
    /**
     * Creates a new character stream from a string
     * @param content the string to build the stream from
     */
    CharStream( std::string content );

    /**
     * Get the next character in the stream
     * @return the next character in the stream, 
     * or 0 if at the end of the stream
     */
    char Next();

    /**
     * Goes back one character in the stream
     */
    void Back();

private:
    std::string content_;
    unsigned index_;
};


#endif