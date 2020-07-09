#include "stdafx.h"

int main( int    /*argc*/
        , char** /*argv*/ )
{
    nSystem::Console console;
    nArt::Drawer drawer;

    const nSystem::Error result = drawer.Draw( console );
    assert( result );
 
    int mainResult = 0;
    if ( !result )
    {
        result.Display( console );
        mainResult = result.GetCode();
    }

    _getch();
    return mainResult;
}