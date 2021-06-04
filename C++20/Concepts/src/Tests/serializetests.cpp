#include "serializetests.h"

#include "serializenumberstests.h"
#include "serializestringstests.h"
#include "serializecontainerstests.h"

//-----------------------------------------------------------------------------
std::size_t tests::SerializeNumbers(std::ostream& inStream)
{
    std::size_t Result = 0;

    Result += SerializeInt(inStream);
    Result += SerializeFloats(inStream);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::SerializeStrings(std::ostream& inStream)
{
    std::size_t Result = 0;

    Result += SerializeString(inStream);
    Result += SerializeWString(inStream);
    Result += SerializeU8String(inStream);
    Result += SerializeU16String(inStream);
    Result += SerializeU32String(inStream);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::SerializeContainers(std::ostream& inStream)
{
    std::size_t Result = 0;

    Result += SerializeSequenceContainers(inStream);
    Result += SerializeAssociativeContainers(inStream);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializeNumbers(std::istream& inStream)
{
    std::size_t Result = 0;

    Result += DeSerializeInt(inStream);
    Result += DeSerializeFloats(inStream);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializeStrings(std::istream& inStream)
{
    std::size_t Result = 0;

    Result += DeSerializeString(inStream);
    Result += DeSerializeWString(inStream);
    Result += DeSerializeU8String(inStream);
    Result += DeSerializeU16String(inStream);
    Result += DeSerializeU32String(inStream);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializeContainers(std::istream& inStream)
{
    std::size_t Result = 0;

    Result += DeSerializeSequenceContainers(inStream);
    Result += DeSerializeAssociativeContainers(inStream);

    return Result;
}
//-----------------------------------------------------------------------------
