#ifndef  UTILS_HPP
#define UTILS_HPP

#include <iostream>

std::string get_current_time ( )
{
    std::time_t now = std::time ( nullptr );
    std::tm time_info;
    localtime_s ( &time_info , &now );

    char buffer[ 80 ];
    strftime ( buffer , sizeof ( buffer ) , "%Y-%m-%d %H:%M:%S" , &time_info );
    return std::string ( buffer );
}

void log_message ( const std::string& message )
{
    std::ofstream log_file ( "log.txt" , std::ios_base::app );
    if ( log_file.is_open ( ) )
    {
        log_file << "[" << get_current_time ( ) << "] " << message << std::endl;
        log_file.close ( );
    }
}

std::string read_key_from_file ( const std::string& file_path )
{
    std::ifstream key_file ( file_path );
    std::string key;
    if ( key_file.is_open ( ) )
    {
        std::getline ( key_file , key );
        key_file.close ( );
    }
    return key;
}

#endif // ! UTILS_HPP
