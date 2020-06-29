#include "stdafx.h"

using namespace nSystem;


Console::Console()
    : m_Handle( GetStdHandle( STD_OUTPUT_HANDLE ) )
{
    assert( m_Handle != INVALID_HANDLE_VALUE );
}

Error Console::MoveCursor( const uint16_ht pX
                         , const uint16_ht pY )
{
    if ( m_Handle == INVALID_HANDLE_VALUE )
    {
        return Error( Error::kInvalidHandle, "Invalid console handle" );
    }

    COORD coord = {};
    coord.X = static_cast<SHORT>( pY );
    coord.Y = static_cast<SHORT>( pX );

    const BOOL lResult = SetConsoleCursorPosition( m_Handle, coord );
    if ( lResult == TRUE )
    {
        return Error();
    }

    return Error( "Failed to set cursor position" );
}

Error Console::SetColor( const BackColor pBackColor
                       , const ForeColor pForeColor )
{
    if ( m_Handle == INVALID_HANDLE_VALUE )
    {
        return Error( Error::kInvalidHandle, "Invalid console handle" );
    }

    const WORD lAttr = static_cast<WORD>( pBackColor ) | static_cast<WORD>( pForeColor );
    const BOOL lResult = SetConsoleTextAttribute( m_Handle, lAttr );

    if ( lResult == TRUE )
    {
        return Error();
    }

    return Error( "Failed to set color" );
}

Error Console::Clear()
{
    const Error resetResp = SetColor( BackColor::Black, ForeColor::White );
    if ( !resetResp )
    {
        return resetResp;
    }
    const int sysRes = system( "cls" );
    if ( sysRes == 0 )
    {
        return Error();
    }

    return Error( "Failed to clear the console" );
}

Error Console::PutString( const char* const pFmt
                        , ... )
{
    if ( m_Handle == INVALID_HANDLE_VALUE )
    {
        return Error( Error::kInvalidHandle, "Invalid console handle" );
    }

    va_list args;
    va_start( args, pFmt );

    printf( pFmt, args );

    va_end( args );

    return Error();
}
