#include "stdafx.h"

using namespace nAsciiArt;
using namespace nSystem;


DocumentDrawer::DocumentDrawer( std::weak_ptr<Document> pAsciiArtDocument )
{
    m_AsciiArtDocumentWeakPtr = std::move( pAsciiArtDocument );
}

Error DocumentDrawer::Draw( IOutput& pOutput ) const
{
    std::shared_ptr<Document> asciiArtDocument = m_AsciiArtDocumentWeakPtr.lock();

    if ( asciiArtDocument == nullptr )
    {
        return nSystem::Error( nSystem::Error::kInvalidDocument, "Invalid ascii art document" );
    }

    for ( const auto& asciiArtObject : asciiArtDocument->GetAsciiArtObjects() )
    {
        if ( const Error res = asciiArtObject->Draw( pOutput ); !res )
        {
            return res;
        }
    }

    return Error();
}
