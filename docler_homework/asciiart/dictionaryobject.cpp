#include "stdafx.h"

using namespace nAsciiArt;


nSystem::Error DictionaryObject::Draw( nSystem::IOutput& pOutput
                                     , const COORD& pBaseCoord ) const
{
    COORD dataRowStartPos = pBaseCoord;

    for ( const std::string& dataRaw : m_DataByRaw )
    {
        const nSystem::Error moveRes = pOutput.MoveCursor( dataRowStartPos );
        dataRowStartPos.Y++;
 
        if ( !moveRes )
        {
            continue;
        }

        if ( const nSystem::Error putRes = pOutput.PutString( "%s", dataRaw.c_str() ); !putRes )
        {
            return putRes;
        }
    }

    return nSystem::Error();
}

void DictionaryObject::AddDataRow( std::string pDataRaw )
{
    m_DataByRaw.push_back( std::move( pDataRaw) );
}
