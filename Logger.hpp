#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string>
#include <iostream>

#define LOG(x) Logger::Log( __FILE__ ": " x );
#define THIS_STR Logger::PointerToString( this )

class Logger
{
public:
    static Logger* logger_;
    static void Log( std::string str );
    static std::string PointerToString( void* ptr );
    Logger( std::string file = "log.out" );
    ~Logger();
    void Write( std::string str );
private:
    std::ofstream out;
};

#endif