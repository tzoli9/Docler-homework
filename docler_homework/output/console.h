#pragma once

namespace nSystem
{
    class Console final : public IOutput
    {
    private:
        HANDLE m_Handle;
        WORD m_wAttributes;

    public:
        Console();
        virtual ~Console() = default;

    public:
        Error MoveCursor( const COORD& pCoord ) override;

        Error SetColor( const BackColor pBackColor
                      , const ForeColor pForeColor ) override;

        Error Clear() override;

        Error SetCursorVisible( bool pVisible ) override;

        Error SaveState() override;

        Error RestoreState() override;

    public:
        Error PutString( const char* const pFmt
                        , ... ) override;
    };
}