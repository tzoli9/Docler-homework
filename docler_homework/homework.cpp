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

int DrawArt( nSystem::Console& pConsole )
{
    nArt::Drawer drawer;

    const nSystem::Error drawResult = drawer.Draw( pConsole );
    assert( drawResult );

    return ExitWithResult( drawResult, pConsole );
}

int DrawAsciiArt( nSystem::Console& pConsole
                , const char* const pFileName )
{
    auto asciiArtDocument = std::make_shared<nAsciiArt::Document>();
    if ( const nSystem::Error loadResult = asciiArtDocument->Load( pFileName ); !loadResult )
    {
        return ExitWithResult( loadResult, pConsole );
    }

    nAsciiArt::DocumentDrawer documentDrawer( asciiArtDocument );
    if ( const nSystem::Error drawResult = documentDrawer.Draw( pConsole ); !drawResult )
    {
        return ExitWithResult( drawResult, pConsole );
    }

    for ( const std::unique_ptr<nAnimation::Animation>& animation : asciiArtDocument->GetAnimations() )
    {
        COORD prevMoveVector = COORD{ 0, 0 };
        asciiArtDocument->InitAnimation();
        animation->StartAnimation( nAnimation::Animation::NowMillis() );

        while ( animation->IsActive() )
        {
            const COORD actualMoveVector = animation->CalcActualMoveVector();

            if ( actualMoveVector != prevMoveVector )
            {
                asciiArtDocument->ActualizeWhenAnimating( actualMoveVector );
 
                if ( const nSystem::Error clearResult = pConsole.Clear(); !clearResult )
                {
                    return ExitWithResult( clearResult, pConsole );
                }

                if ( const nSystem::Error drawResult = documentDrawer.Draw( pConsole ); !drawResult )
                {
                    return ExitWithResult( drawResult, pConsole );
                }

                prevMoveVector = actualMoveVector;
            }

            Sleep( 16 );
            animation->ActualizeAnimation( nAnimation::Animation::NowMillis() );
        }
    }

    return ExitWithResult( nSystem::Error(), pConsole );
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

    if ( argc < 2 )
    {
        return ExitWithResult( nSystem::Error( nSystem::Error::kInvalidNumberOfArguments, "Invalid number of arguments" ), console);
    }

    const char* const drawerType = argv[1];

    if ( strcmp( drawerType, "art" ) == 0 )
    {
        return DrawArt( console );
    }

    if ( strcmp( drawerType, "asciiart" ) == 0 )
    {
        if ( argc != 3 )
        {
            return ExitWithResult( nSystem::Error( nSystem::Error::kInvalidNumberOfArguments, "Invalid number of arguments" ), console );
        }

        const char* const fileName = argv[2];
        return DrawAsciiArt( console, fileName );
    }

    return ExitWithResult( nSystem::Error( nSystem::Error::kInvalidNumberOfArguments, "Invalid drawer type argument" ), console );
}
