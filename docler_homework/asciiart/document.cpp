#include "stdafx.h"

using namespace nAsciiArt;
using namespace nSystem;


namespace
{
    constexpr const char* const kDictionaryBegin = "<![DICTIONARY[";
    constexpr const char* const kDictionaryEnd   = "]]>DICTIONARY";

    constexpr const char* const kDictionaryItemBegin = "<![ITEM[";
    constexpr const char* const kDictionaryItemEnd   = "]]>ITEM";

    constexpr const char* const kObjectsBegin = "<![OBJECTS[";
    constexpr const char* const kObjectsEnd   = "]]>OBJECTS";

    constexpr const char* const kAnimationsBegin = "<![ANIMATIONS[";
    constexpr const char* const kAnimationsEnd   = "]]>ANIMATIONS";
}


std::vector<std::string> Tokenize( const std::string& pInputString )
{
    std::vector<std::string> outStrings;

    std::string::size_type begin = 0;
    for (std::string::size_type end = 0; (end = pInputString.find( " ", end )) != std::string::npos; ++end )
    {
        outStrings.push_back( pInputString.substr( begin, end - begin ) );
        begin = end + 1;
    }

    outStrings.push_back( pInputString.substr( begin ) );

    return outStrings;
}

Error Document::LoadDictionaryObject( std::ifstream& pInFile
                                    , DictionaryObject& pAsciiArtDictionaryObject )
{
    for ( std::string line; std::getline( pInFile, line ); )
    {
        if ( line == kDictionaryItemEnd )
        {
            return Error();
        }
 
        pAsciiArtDictionaryObject.AddDataRow( line );
    }

    return Error( Error::kErrorWhileLoadingDocument, "Failed to load ascii art object" );
}

Error Document::LoadDictionary( std::ifstream& pInFile )
{
    for ( std::string line; std::getline( pInFile, line ); )
    {
        if ( line == kDictionaryEnd )
        {
            return Error();
        }

        if ( line.find( kDictionaryItemBegin ) == 0 )
        {
            const std::string key( line.substr( strlen( kDictionaryItemBegin ) ) );
            auto asciiArtDictionaryObject = std::make_shared<DictionaryObject>();

            if ( const Error res = LoadDictionaryObject( pInFile, *asciiArtDictionaryObject ); !res )
            {
                return res;
            }

            m_Dictionary.emplace( key, std::move( asciiArtDictionaryObject ) );
        }
    }

    return Error( Error::kErrorWhileLoadingDocument, "Failed to load ascii art dictionary" );
}

Error Document::LoadObjects( std::ifstream& pInFile )
{
    for ( std::string line; std::getline( pInFile, line ); )
    {
        if ( line == kObjectsEnd )
        {
            return Error();
        }

        const std::vector<std::string> tokenizedLine = Tokenize( line );

        if ( tokenizedLine.size() != 5 )
        {
            return Error( Error::kErrorWhileLoadingDocument, "Failed to load ascii art objects" );
        }

        const std::string& key = tokenizedLine[0];
        const auto dictionaryIter = m_Dictionary.find( key );
        if ( dictionaryIter == m_Dictionary.end() )
        {
            return Error( Error::kErrorWhileLoadingDocument, "Invalid dictionary key" );
        }

        const std::string& coordXStr = tokenizedLine[1];
        SHORT coordX = 0;
        if ( const Error coordXLoadRes = Document::ParseShort( coordXStr, coordX ); !coordXLoadRes )
        {
            return coordXLoadRes;
        }

        const std::string& coordYStr = tokenizedLine[2];
        SHORT coordY = 0;
        const Error coordYLoadRes = Document::ParseShort( coordYStr, coordY );
        if ( !coordYLoadRes )
        {
            return coordYLoadRes;
        }

        const std::string& backgroundStr = tokenizedLine[3];
        IOutput::BackColor backgroundColor = IOutput::BackColor::Black;
        const Error bgColorLoadRes = Document::ParseBackgroundColor( backgroundStr, backgroundColor );
        if ( !bgColorLoadRes )
        {
            return bgColorLoadRes;
        }

        const std::string& foregroundStr = tokenizedLine[4];
        IOutput::ForeColor foregroundColor = IOutput::ForeColor::White;
        const Error fgColorLoadRes = Document::ParseForegroundColor( foregroundStr, foregroundColor );
        if ( !fgColorLoadRes )
        {
            return fgColorLoadRes;
        }

        auto asciiArtObject = std::make_unique<DocObject>();
        asciiArtObject->SetDictionaryObject( dictionaryIter->second );
        asciiArtObject->SetBaseCoord( COORD{ coordX, coordY } );
        asciiArtObject->SetBackColor( backgroundColor );
        asciiArtObject->SetForeColor( foregroundColor );
        m_AsciiArtObjects.push_back( std::move( asciiArtObject ) );
    }

    return Error( Error::kErrorWhileLoadingDocument, "Failed to load ascii art objects" );
}

nSystem::Error Document::LoadAnimations( std::ifstream& pInFile )
{
    for ( std::string line; std::getline( pInFile, line ); )
    {
        if ( line == kAnimationsEnd )
        {
            return Error();
        }

        const std::vector<std::string> tokenizedLine = Tokenize( line );

        if ( tokenizedLine.size() != 4 )
        {
            return Error( Error::kErrorWhileLoadingDocument, "Failed to load animations" );
        }

        const std::string& accelerationString = tokenizedLine[0];
        nAnimation::Animation::Acceleration acceleration = nAnimation::Animation::Acceleration::Linear;
        const Error accelerationLoadRes = Document::ParseAcceleration( accelerationString, acceleration );
        if ( !accelerationLoadRes )
        {
            return accelerationLoadRes;
        }

        const std::string& durationStr = tokenizedLine[1];
        SHORT duration = 0;
        const Error durationLoadRes = Document::ParseShort( durationStr, duration );
        if ( !durationLoadRes )
        {
            return durationLoadRes;
        }

        if ( duration <= 0 )
        {
            return Error( Error::kErrorWhileLoadingDocument, "Invalid duration" );
        }

        const std::string& moveVectorXStr = tokenizedLine[2];
        SHORT moveVectorX = 0;
        if ( const Error moveVectorXLoadRes = Document::ParseShort( moveVectorXStr, moveVectorX ); !moveVectorXLoadRes )
        {
            return moveVectorXLoadRes;
        }

        const std::string& moveVectorYStr = tokenizedLine[3];
        SHORT moveVectorY = 0;
        if ( const Error moveVectorYLoadRes = Document::ParseShort( moveVectorYStr, moveVectorY ); !moveVectorYLoadRes )
        {
            return moveVectorYLoadRes;
        }

        auto animation = std::make_unique<nAnimation::Animation>( acceleration, duration, COORD{ moveVectorX, moveVectorY } );
        m_Animations.push_back( std::move( animation ) );
    }

    return Error( Error::kErrorWhileLoadingDocument, "Failed to load animations" );
}

Error Document::ParseShort( const std::string& pShortString
                          , SHORT& pShort )
{
    pShort = 0;

    try
    {
        std::size_t endIndex = 0;
        const int parsedInt = std::stoi( pShortString, &endIndex );

        if ( pShortString.length() != endIndex )
        {
            return Error( Error::kErrorWhileLoadingDocument, "Failed to parse number" );
        }

        if ( parsedInt < std::numeric_limits<SHORT>::min() || parsedInt > std::numeric_limits<SHORT>::max() )
        {
            return Error( Error::kErrorWhileLoadingDocument, "Number is out of range" );
        }

        pShort = static_cast<SHORT>(parsedInt);
    }
    catch ( const std::invalid_argument& )
    {
        return Error( Error::kErrorWhileLoadingDocument, "Failed to parse number" );
    }
    catch ( std::out_of_range& )
    {
        return Error( Error::kErrorWhileLoadingDocument, "Number is out of range" );
    }
    catch ( ... )
    {
        return Error( Error::kErrorWhileLoadingDocument, "Failed to parse number" );
    }

    return Error();
}

Error Document::ParseForegroundColor( const std::string& pColorString
                                    , IOutput::ForeColor& pForegroundColor )
{
    if ( pColorString == "white" )
    {
        pForegroundColor = IOutput::ForeColor::White;
        return Error();
    }

    if ( pColorString == "black" )
    {
        pForegroundColor = IOutput::ForeColor::Black;
        return Error();
    }

    if ( pColorString == "red" )
    {
        pForegroundColor = IOutput::ForeColor::Red;
        return Error();
    }

    if ( pColorString == "green" )
    {
        pForegroundColor = IOutput::ForeColor::Green;
        return Error();
    }

    if ( pColorString == "blue" )
    {
        pForegroundColor = IOutput::ForeColor::Blue;
        return Error();
    }

    return Error( Error::kErrorWhileLoadingDocument, "Failed to parse foreground color" );
}

Error Document::ParseBackgroundColor( const std::string& pColorString
                                    , IOutput::BackColor& pBackgroundColor )
{
    if ( pColorString == "white" )
    {
        pBackgroundColor = IOutput::BackColor::White;
        return Error();
    }

    if ( pColorString == "black" )
    {
        pBackgroundColor = IOutput::BackColor::Black;
        return Error();
    }

    if ( pColorString == "red" )
    {
        pBackgroundColor = IOutput::BackColor::Red;
        return Error();
    }

    if ( pColorString == "green" )
    {
        pBackgroundColor = IOutput::BackColor::Green;
        return Error();
    }

    if ( pColorString == "blue" )
    {
        pBackgroundColor = IOutput::BackColor::Blue;
        return Error();
    }

    return Error( Error::kErrorWhileLoadingDocument, "Failed to parse background color" );
}

nSystem::Error Document::ParseAcceleration( const std::string& pAccelerationString
                                          , nAnimation::Animation::Acceleration& pAcceleration )
{
    if ( pAccelerationString == "linear" )
    {
        pAcceleration = nAnimation::Animation::Acceleration::Linear;
        return Error();
    }

    if ( pAccelerationString == "cubic" )
    {
        pAcceleration = nAnimation::Animation::Acceleration::Cubic;
        return Error();
    }

    if ( pAccelerationString == "bounce" )
    {
        pAcceleration = nAnimation::Animation::Acceleration::Bounce;
        return Error();
    }

    return Error( Error::kErrorWhileLoadingDocument, "Failed to parse acceleration" );
}

Error Document::Load( const char* const pFileName )
{
    m_AsciiArtObjects.clear();

    std::ifstream inFile( pFileName, std::ios::in );
 
    if ( !inFile.is_open() )
    {
        return Error( Error::kErrorWhileLoadingDocument, "Failed to open document" );
    }

    for ( std::string line; std::getline( inFile, line ); )
    {
        if ( line == kDictionaryBegin )
        {
            if ( const Error res = LoadDictionary( inFile ); !res )
            {
                return res;
            }
        }
        else if ( line == kObjectsBegin )
        {
            if ( const Error res = LoadObjects( inFile ); !res )
            {
                return res;
            }
        }
        else if ( line == kAnimationsBegin )
        {
            if ( const Error res = LoadAnimations( inFile ); !res )
            {
                return res;
            }
        }
        else
        {
            return Error( Error::kErrorWhileLoadingDocument, "Invalid document section" );
        }
    }

    return Error();
}

const std::vector<std::unique_ptr<DocObject>>& Document::GetAsciiArtObjects() const
{
    return m_AsciiArtObjects;
}

const std::vector<std::unique_ptr<nAnimation::Animation>>& Document::GetAnimations() const
{
    return m_Animations;
}

void Document::InitAnimation()
{
    for ( const std::unique_ptr<DocObject>& docObject : m_AsciiArtObjects )
    {
        docObject->InitAnimation();
    }
}

void Document::ActualizeWhenAnimating( const COORD& pMoveVector )
{
    for ( const std::unique_ptr<DocObject>& docObject : m_AsciiArtObjects )
    {
        docObject->ActualizeWhenAnimating( pMoveVector );
    }
}
