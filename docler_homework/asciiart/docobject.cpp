#include "stdafx.h"

using namespace nAsciiArt;


DocObject::DocObject()
{
    m_BackgroundColor = nSystem::IOutput::BackColor::Black;
    m_ForegroundColor = nSystem::IOutput::ForeColor::White;

    m_BaseCoord = COORD{ 0, 0 };
    m_AnimationStartBaseCoord = COORD{ 0, 0 };
}

nSystem::Error DocObject::Draw( nSystem::IOutput& pOutput ) const
{
    std::shared_ptr<DictionaryObject> dictionaryObject = m_DictionaryObjectWeakPtr.lock();

    if ( dictionaryObject == nullptr )
    {
        return nSystem::Error( nSystem::Error::kInvalidObject, "Invalid ascii art object" );
    }

    if ( const nSystem::Error setColorRes = pOutput.SetColor( m_BackgroundColor, m_ForegroundColor ); !setColorRes )
    {
        return setColorRes;
    }

    const nSystem::Error drawRes = dictionaryObject->Draw( pOutput, m_BaseCoord );

    return drawRes;
}

void DocObject::SetBaseCoord( const COORD& pBaseCoord )
{
    m_BaseCoord = pBaseCoord;
}

void DocObject::SetBackColor( const nSystem::IOutput::BackColor pBackgroundColor )
{
    m_BackgroundColor = pBackgroundColor;
}

void DocObject::SetForeColor( const nSystem::IOutput::ForeColor pBackgroundColor )
{
    m_ForegroundColor = pBackgroundColor;
}

void DocObject::SetDictionaryObject( std::weak_ptr<DictionaryObject> pAsciiArtDictionaryObject )
{
    m_DictionaryObjectWeakPtr = std::move( pAsciiArtDictionaryObject );
}

void DocObject::InitAnimation()
{
    m_AnimationStartBaseCoord = m_BaseCoord;
}

void DocObject::ActualizeWhenAnimating( const COORD& pMoveVector )
{
    m_BaseCoord = m_AnimationStartBaseCoord + pMoveVector;
}
