#pragma once

namespace nAnimation
{
    class Animation final
    {
    public:
        enum class Acceleration
        {
              Linear
            , Cubic
            , Bounce
        };

    private:
        int64_ht m_StartAnimationTime;
        int64_ht m_EndAnimationTime;

        bool m_Active;

        int64_ht m_Duration;
        Acceleration m_Acceleration;

        double m_Ratio;
        COORD m_MoveVector;

    public:
        static int64_ht NowMillis();

        Animation( const Acceleration pAcceleration
                 , const int64_ht pDuration
                 , const COORD& pMoveVector );

        void StartAnimation( const int64_ht pStartTime );
        void ActualizeAnimation( const int64_ht pNow );
        COORD CalcActualMoveVector() const;
        bool IsActive() const;
    };
}
