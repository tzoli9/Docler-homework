#pragma once

namespace nArt
{
    class Drawer final
    {
    private:
        struct sData
        {
            COORD             coord;
            const char* const text = nullptr;
        };


        using CoordList = std::list<sData>;

    private:
        static const nSystem::IOutput::BackColor kRedBackground;
        static const nSystem::IOutput::ForeColor kWhiteForeground;

        static const CoordList kCoords;

    public:
        nSystem::Error Draw( nSystem::IOutput& pOutput );
    };
}
