#pragma once


namespace nAsciiArt
{
    class Document final
    {
    private:
        std::vector<std::unique_ptr<DocObject>> m_AsciiArtObjects;
        std::map<std::string, std::shared_ptr<DictionaryObject>> m_Dictionary;

        nSystem::Error LoadDictionaryObject( std::ifstream& pInFile
                                           , DictionaryObject& pAsciiArtDictionaryObject );

        nSystem::Error LoadDictionary( std::ifstream& pInFile );

        nSystem::Error LoadObjects( std::ifstream& pInFile );

        static nSystem::Error ParseShort( const std::string& pShortString
                                        , SHORT& pShort );

        static nSystem::Error ParseForegroundColor( const std::string& pColorString
                                                  , nSystem::IOutput::ForeColor& pForegroundColor );

        static nSystem::Error ParseBackgroundColor( const std::string& pColorString
                                                  , nSystem::IOutput::BackColor& pBackgroundColor );

    public:
        nSystem::Error Load( const char* const pFileName );
        const std::vector<std::unique_ptr<DocObject>>& GetAsciiArtObjects() const;
    };
}
