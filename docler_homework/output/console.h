#pragma once

namespace nSystem
{
    class Console final : public IOutput
    {
    private:
        HANDLE m_Handle;

    public:
        Console();
        virtual ~Console() = default;

    public:
        Error MoveCursor( const COORD& pCoord ) override;

        Error SetColor( const BackColor pBackColor
                      , const ForeColor pForeColor ) override;

        Error Clear() override;

    public:
        Error PutString( const char* const pFmt
                        , ... ) override;

    };
}