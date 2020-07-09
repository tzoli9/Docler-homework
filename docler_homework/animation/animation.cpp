#include "stdafx.h"

using namespace nAnimation;


int64_ht Animation::NowMillis()
{
    int64_ht value = 1000;
    timeb tp;
    ftime( &tp );
    value *= tp.time;
    return (value + tp.millitm);
}

Animation::Animation( const Acceleration pAcceleration
                    , const int64_ht pDuration
                    , const COORD& pMoveVector )
    : m_Acceleration( pAcceleration )
    , m_Duration( pDuration )
    , m_MoveVector( pMoveVector )
{
    m_StartAnimationTime = 0;
    m_EndAnimationTime = 0;

    m_Active = false;
    m_Ratio = 0.0;
}

void Animation::StartAnimation( const int64_ht pStartTime )
{
    m_StartAnimationTime = pStartTime;
    m_EndAnimationTime = m_StartAnimationTime + m_Duration;

    m_Active = true;
}

void Animation::ActualizeAnimation( const int64_ht pNow )
{
    if ( !m_Active )
    {
        return;
    }

    if ( pNow <= m_StartAnimationTime )
    {
        m_Ratio = 0.0;
        return;
    }

    if ( pNow >= m_EndAnimationTime )
    {
        m_Ratio = 1.0;
        m_Active = false;
        return;
    }

    m_Ratio = static_cast<double>( pNow - m_StartAnimationTime ) / static_cast<double>( m_Duration );

    switch ( m_Acceleration )
    {
        case Acceleration::Linear:
        {
            break;
        }
        case Acceleration::Cubic:
        {
            m_Ratio -= 1.0;
            m_Ratio = m_Ratio * m_Ratio * m_Ratio + 1.0;
            break;
        }
        case Acceleration::Bounce:
        {
            if ( m_Ratio <= 0.36363636 )
            {
                m_Ratio = 7.5625 * m_Ratio * m_Ratio;
            }
            else if ( m_Ratio <= 0.72727272 )
            {
                m_Ratio -= 0.54545454;
                m_Ratio = 7.5625 * m_Ratio * m_Ratio + 0.75;
            }
            else if ( m_Ratio <= 0.90909090 )
            {
                m_Ratio -= 0.81818181;
                m_Ratio = 7.5625 * m_Ratio * m_Ratio + 0.9375;
            }
            else
            {
                m_Ratio -= 0.95454545;
                m_Ratio = 7.5625*m_Ratio * m_Ratio + 0.984375;
            }

            break;
        }
    }
}

COORD Animation::CalcActualMoveVector() const
{
    assert( m_Active );

    COORD actualMoveVector{ 0, 0 };
    actualMoveVector.X = static_cast<SHORT>( round( m_MoveVector.X * m_Ratio ) );
    actualMoveVector.Y = static_cast<SHORT>( round( m_MoveVector.Y * m_Ratio ) );

    return actualMoveVector;
}

bool Animation::IsActive() const
{
    return m_Active;
}
