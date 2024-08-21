#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <ctime>
#include "auth.hpp"
#include "utils.hpp"
#include "skStr.h"

using namespace KeyAuth;

std::string name = skCrypt ( "" ).decrypt ( );
std::string ownerid = skCrypt ( "" ).decrypt ( );
std::string secret = skCrypt ( "" ).decrypt ( );
std::string version = skCrypt ( "" ).decrypt ( );
std::string url = skCrypt ( "https://keyauth.win/api/1.2/" ).decrypt ( );
std::string path = skCrypt ( "" ).decrypt ( );
api KeyAuthApp ( name , ownerid , secret , version , url , path );

void validate_key ( const std::string& key )
{
    KeyAuthApp.init ( );
    if ( !KeyAuthApp.response.success )
    {
        log_message ( "[softguard] couldn't setup keyauth" );
        TerminateProcess ( GetCurrentProcess ( ) , 1 );
        return;
    }

    KeyAuthApp.license ( key );
    if ( !KeyAuthApp.response.success )
    {
        log_message ( "[softguard] invalid key" );
        TerminateProcess ( GetCurrentProcess ( ) , 1 );
        return;
    }

    return;
}

void key_validation_thread ( )
{
    std::string key = read_key_from_file ( "key.bin" );

    if ( key.empty ( ) )
    {
        log_message ( "[softguard] key file is empty" );
        TerminateProcess ( GetCurrentProcess ( ) , 1 );
        return;
    }

    validate_key ( key );

    log_message ( "[softguard] valid key, launching program" );
}

BOOL APIENTRY DllMain ( HMODULE hModule , DWORD ul_reason_for_call , LPVOID lpReserved )
{
    switch ( ul_reason_for_call )
    {
    case DLL_PROCESS_ATTACH:
    {
        name.clear ( ); ownerid.clear ( ); secret.clear ( ); version.clear ( ); url.clear ( );

        std::thread validation_thread ( key_validation_thread );
        validation_thread.detach ( );

        break;
    }
    case DLL_PROCESS_DETACH:
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}
