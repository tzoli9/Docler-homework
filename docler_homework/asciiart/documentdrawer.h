#pragma once


namespace nAsciiArt
{
    class DocumentDrawer final
    {
    private:
        std::weak_ptr<Document> m_AsciiArtDocumentWeakPtr;
    public:
        DocumentDrawer( std::weak_ptr<Document> pAsciiArtDocument );
        nSystem::Error Draw( nSystem::IOutput& pOutput ) const;
    };
}
