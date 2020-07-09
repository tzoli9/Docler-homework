#pragma once

namespace nSystem
{
    class __declspec( novtable ) IOutput
    {
    public:
        enum class ForeColor
        {
              White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
            , Black = 0
            , Red   = FOREGROUND_RED
            , Green = FOREGROUND_GREEN
            , Blue  = FOREGROUND_BLUE
        };

        enum class BackColor
        {
              White = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
            , Black = 0
            , Red   = BACKGROUND_RED
            , Green = BACKGROUND_GREEN
            , Blue  = BACKGROUND_BLUE
        };

    protected:
        IOutput() = default;

    public:
        virtual ~IOutput() = default;


    public:
        virtual Error MoveCursor( const COORD& pCoord ) = 0;


        virtual Error SetColor( const BackColor pBackColor
                              , const ForeColor pForeColor ) = 0;

        virtual Error Clear() = 0;

    public:
        virtual Error PutString( const char* const pFmt
                               , ... ) = 0;
    };
}
