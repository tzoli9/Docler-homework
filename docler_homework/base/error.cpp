#include "stdafx.h"

using namespace nSystem;

void Error::Display( IOutput& aOutput ) const
{
    aOutput.MoveCursor( 0, 0 );
    aOutput.PutString( "Error: %d - %s", m_Code, m_UserMessage );
}
