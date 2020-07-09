#pragma once

namespace nAsciiArt
{
    class DictionaryObject final
    {
    private:
        std::vector<std::string> m_DataByRaw;

    public:
        nSystem::Error Draw( nSystem::IOutput& pOutput
                           , const COORD& pBaseCoord ) const;

        void AddDataRow( std::string pDataRaw );
    };
}
