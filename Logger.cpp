#include "Logger.hpp"
#include <sstream>

Logger* Logger::logger_ = nullptr;

void Logger::Log( std::string str )
{
    if( !Logger::logger_ )
    {
        Logger::logger_ = new Logger();
    }
    Logger::logger_->Write( str + "\n" );
}

std::string Logger::PointerToString( void* ptr )
{
    const void * address = static_cast<const void*>(ptr);
    std::stringstream ss;
    ss << address;  
    std::string name = ss.str(); 
    return name;
}

Logger::Logger( std::string file )
    : out( file )
{

}

Logger::~Logger()
{
    out.close();
}

void Logger::Write( std::string str )
{
    out << str;
    out.flush();
}