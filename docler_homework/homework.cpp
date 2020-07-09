#include "stdafx.h"


int ExitWithResult( const nSystem::Error& pResult
                  , nSystem::Console& pConsole )
{
    if ( !pResult )
    {
        pResult.Display( pConsole );
    }

    _getch();
    pConsole.SetCursorVisible( true );
    pConsole.RestoreState();

    return pResult.GetCode();
}

int main( int    argc
        , char** argv )
{
    nSystem::Console console;

    if ( const nSystem::Error saveStateResult = console.SaveState(); !saveStateResult )
    {
        return ExitWithResult( saveStateResult, console );
    }

    if ( const nSystem::Error clearResult = console.Clear(); !clearResult )
    {
        return ExitWithResult( clearResult, console );
    }

    if ( const nSystem::Error setCursorVisibleResult = console.SetCursorVisible( false ); !setCursorVisibleResult )
    {
        return ExitWithResult( setCursorVisibleResult, console );
    }

    if ( argc != 2 )
    {
        return ExitWithResult( nSystem::Error( nSystem::Error::kInvalidNumberOfArguments, "Invalid number of arguments" ), console);
    }

    const char* const fileName = argv[1];
    auto asciiArtDocument = std::make_shared<nAsciiArt::Document>();
    if ( const nSystem::Error loadResult = asciiArtDocument->Load( fileName ); !loadResult )
    {
        return ExitWithResult( loadResult, console);
    }

    nAsciiArt::DocumentDrawer documentDrawer( asciiArtDocument );
    if ( const nSystem::Error drawResult = documentDrawer.Draw( console ); !drawResult )
    {
        return ExitWithResult( drawResult, console);
    }

    return ExitWithResult( nSystem::Error(), console );
}
