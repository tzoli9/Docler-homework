#pragma once


inline bool operator==( const COORD& pCoord1
                      , const COORD& pCoord2 )
{
    return ( pCoord1.X == pCoord2.X && pCoord1.Y == pCoord2.Y );
}

inline bool operator!=( const COORD& pCoord1
                      , const COORD& pCoord2 )
{
    return !operator==( pCoord1, pCoord2 );
}

inline COORD operator+( const COORD& pCoord1
                      , const COORD& pCoord2 )
{
    return { pCoord1.X + pCoord2.X, pCoord1.Y + pCoord2.Y };
}
