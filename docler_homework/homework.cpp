#include "stdafx.h"

int main( int    argc
        , char** argv )
{
    nSystem::Console console;
    nArt::Drawer drawer;

    const nSystem::Error result = drawer.Draw( console );
    assert( result );
    if ( !result )
    {
        result.Display( console )
        return result.GetCode();
    }

    getchar();
    return 0;
}