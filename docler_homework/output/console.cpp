#include "stdafx.h"

using namespace nSystem;


Console::Console()
    : m_Handle( GetStdHandle( STD_OUTPUT_HANDLE ) )
{
    assert( m_Handle != INVALID_HANDLE_VALUE );
}

Error Console::MoveCursor( const COORD& pCoord )
{
    if ( m_Handle == INVALID_HANDLE_VALUE )
    {
        return Error( Error::kInvalidHandle, "Invalid console handle" );
    }

    const BOOL lResult = SetConsoleCursorPosition( m_Handle, pCoord );
    if ( lResult == FALSE )
    {
        return Error( "Failed to set cursor position" );
    }

    return Error();
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

    if ( lResult == FALSE )
    {
        return Error( "Failed to set color" );
    }

    return Error();
}

Error Console::Clear()
{
    const Error lResetResp = SetColor( BackColor::Black, ForeColor::White );
    if ( !lResetResp )
    {
        return lResetResp;
    }
 
    const int lSysRes = system( "cls" );
    if ( lSysRes != 0 )
    {
        return Error( "Failed to clear the console" );
    }

    return Error();
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

    vprintf( pFmt, args );

    va_end( args );

    return Error();
}
