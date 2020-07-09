#pragma once

namespace nAsciiArt
{
    class DocObject final
    {
    private:
        nSystem::IOutput::BackColor m_BackgroundColor;
        nSystem::IOutput::ForeColor m_ForegroundColor;

        COORD m_BaseCoord;
        COORD m_AnimationStartBaseCoord;
        std::weak_ptr<DictionaryObject> m_DictionaryObjectWeakPtr;

    public:
        DocObject();
        nSystem::Error Draw( nSystem::IOutput& pOutput ) const;

        void SetBaseCoord( const COORD& pBaseCoord );
        void SetBackColor( const nSystem::IOutput::BackColor pBackgroundColor );
        void SetForeColor( const nSystem::IOutput::ForeColor pBackgroundColor );
        void SetDictionaryObject( std::weak_ptr<DictionaryObject> pAsciiArtDictionaryObject );

        void InitAnimation();
        void ActualizeWhenAnimating( const COORD& pMoveVector );
    };
}
