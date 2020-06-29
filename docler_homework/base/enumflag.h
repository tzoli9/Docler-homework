#pragma once

#pragma once

#define ENUM_FLAG_OPERATOR( _pType, _pOperator )                                                                      \
    inline _pType operator _pOperator ( const _pType pEnum1, const _pType pEnum2 )                                    \
    {                                                                                                                 \
        return static_cast<_pType>( static_cast<uint64_ht>( pEnum1 ) _pOperator static_cast<uint64_ht>( pEnum2 ) );   \
    }

#define ENUM_FLAG( _pType )          \
    ENUM_FLAG_OPERATOR( _pType, |  ) \
    ENUM_FLAG_OPERATOR( _pType, &  ) \
    ENUM_FLAG_OPERATOR( _pType, ^  )