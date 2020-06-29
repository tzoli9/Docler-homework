#pragma once

namespace nSystem
{
    class IOutput;

    class Error final
    {
    public:
        static constexpr const int32_ht kNoError       =  0;
        static constexpr const int32_ht kInvalidHandle = -1;

    private:
        int32_ht          m_Code;
        const char* const m_UserMessage;

    public:
        inline Error();

        inline Error( const int32_ht    pCode
                    , const char* const pUserMessage );

        inline Error( const char* const pUserMessage );

    public:
        int32_ht GetCode() const;
        inline const char* const GetUserMessage() const;

    public:
        inline bool operator==( const bool aRhs ) const;
        inline bool operator!=( const bool aRhs ) const;

        inline bool operator==( const int32_ht aRhs ) const;
        inline bool operator!=( const int32_ht aRhs ) const;

        inline operator bool() const;

    public:
        void Display( IOutput& aOutput ) const;
    };

    inline Error::Error()
        : m_Code       ( kNoError )
        , m_UserMessage( nullptr  )
    {}

    inline Error::Error( const int32_ht    pCode
                       , const char* const pUserMessage )
        : m_Code       ( pCode        )
        , m_UserMessage( pUserMessage )
    {}

    inline Error::Error( const char* const pUserMessage )
        : Error( GetLastError()
               , pUserMessage )
    {}

    int32_ht Error::GetCode() const
    {
        return m_Code;
    }

    inline const char* const Error::GetUserMessage() const
    {
        return m_UserMessage;
    }

    inline bool Error::operator==( const bool aRhs ) const
    {
        if ( aRhs )
        {
            return m_Code == kNoError;
        }

        return m_Code != kNoError;
    }

    inline bool Error::operator!=( const bool aRhs ) const
    {
        return !operator==( aRhs );
    }

    inline bool Error::operator==( const int32_ht aRhs ) const
    {
        return m_Code == aRhs;
    }

    inline bool Error::operator!=( const int32_ht aRhs ) const
    {
        return !operator==( aRhs );
    }

    inline Error::operator bool() const
    {
        return m_Code == kNoError;
    }
}
