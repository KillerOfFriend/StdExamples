#include "serializestringstests.h"

#include <cassert>

#include "Serializer/Serializer.hpp"

static const std::string     Str     = "std::string";
static const std::wstring    wStr    = L"std::wstring";
static const std::u8string   u8Str   = u8"std::u8string";
static const std::u16string  u16Str  = u"std::u16string";
static const std::u32string  u32Str  = U"std::u32string";

//-----------------------------------------------------------------------------
std::size_t tests::SerializeString(std::ostream& inStream)
{
    return Serializer<std::string>::serialize(inStream, Str);
}
//-----------------------------------------------------------------------------
std::size_t tests::SerializeWString(std::ostream& inStream)
{
    return Serializer<std::wstring>::serialize(inStream, wStr);
}
//-----------------------------------------------------------------------------
std::size_t tests::SerializeU8String(std::ostream& inStream)
{
    return Serializer<std::u8string>::serialize(inStream, u8Str);
}
//----------------------------------------------------------------------------
std::size_t tests::SerializeU16String(std::ostream& inStream)
{
    return Serializer<std::u16string>::serialize(inStream, u16Str);
}
//-----------------------------------------------------------------------------
std::size_t tests::SerializeU32String(std::ostream& inStream)
{
   return Serializer<std::u32string>::serialize(inStream, u32Str);
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializeString(std::istream& inStream)
{
    std::size_t Result = 0;

    std::string     lStr     = "";
    Result = Serializer<std::string>::deserialize(inStream, lStr);
    assert(lStr == Str);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializeWString(std::istream& inStream)
{
    std::size_t Result = 0;

    std::wstring     lwStr     = L"";
    Result = Serializer<std::wstring>::deserialize(inStream, lwStr);
    assert(lwStr == wStr);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializeU8String(std::istream& inStream)
{
    std::size_t Result = 0;

    std::u8string     lu8Str     = u8"";
    Result = Serializer<std::u8string>::deserialize(inStream, lu8Str);
    assert(lu8Str == u8Str);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializeU16String(std::istream& inStream)
{
    std::size_t Result = 0;

    std::u16string     lu16Str     = u"";
    Result = Serializer<std::u16string>::deserialize(inStream, lu16Str);
    assert(lu16Str == u16Str);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializeU32String(std::istream& inStream)
{
    std::size_t Result = 0;

    std::u32string     lu32Str     = U"";
    Result = Serializer<std::u32string>::deserialize(inStream, lu32Str);
    assert(lu32Str == u32Str);

    return Result;
}
//-----------------------------------------------------------------------------
