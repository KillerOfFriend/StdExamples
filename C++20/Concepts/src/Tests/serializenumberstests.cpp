#include "serializenumberstests.h"

#include <cassert>

#include "Serializer/Serializer.hpp"

constexpr std::int8_t   i8      = -8;
constexpr std::uint8_t  ui8     = 8;
constexpr std::int16_t  i16     = -16;
constexpr std::uint16_t ui16    = 16;
constexpr std::int32_t  i32     = -32;
constexpr std::uint32_t ui32    = 32;
constexpr std::int64_t  i64     = -64;
constexpr std::uint64_t ui64    = 64;

constexpr float         f32     = 32.0f;
constexpr double        d64     = 64.0;

//-----------------------------------------------------------------------------
std::size_t tests::SerializeInt(std::ostream& inStream)
{   // Сериализация базовых типов данных (целых)
    std::size_t Result = 0;

    Result += Serializer<std::int8_t>::serialize(inStream, i8);
    Result += Serializer<std::uint8_t>::serialize(inStream, ui8);

    Result += Serializer<std::int16_t>::serialize(inStream, i16);
    Result += Serializer<std::uint16_t>::serialize(inStream, ui16);

    Result += Serializer<std::int32_t>::serialize(inStream, i32);
    Result += Serializer<std::uint32_t>::serialize(inStream, ui32);

    Result += Serializer<std::int64_t>::serialize(inStream, i64);
    Result += Serializer<std::uint64_t>::serialize(inStream, ui64);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::SerializeFloats(std::ostream& inStream)
{   // Сериализация базовых типов данных (с плавающей запятой)
    std::size_t Result = 0;

    Result += Serializer<float>::serialize(inStream, f32);
    Result += Serializer<double>::serialize(inStream, d64);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializeInt(std::istream& inStream)
{
    std::size_t Result = 0;

    {
        std::int8_t   li8      = 0;
        std::uint8_t  lui8     = 0;

        Result += Serializer<std::int8_t>::deserialize(inStream, li8);
        Result += Serializer<std::uint8_t>::deserialize(inStream, lui8);

        assert(li8 == i8);
        assert(lui8 == ui8);
    }

    {
        std::int16_t  li16     = 0;
        std::uint16_t lui16    = 0;

        Result += Serializer<std::int16_t>::deserialize(inStream, li16);
        Result += Serializer<std::uint16_t>::deserialize(inStream, lui16);

        assert(li16 == i16);
        assert(lui16 == ui16);
    }

    {
        std::int32_t  li32     = 0;
        std::uint32_t lui32    = 0;

        Result += Serializer<std::int32_t>::deserialize(inStream, li32);
        Result += Serializer<std::uint32_t>::deserialize(inStream, lui32);

        assert(li32 == i32);
        assert(lui32== ui32);
    }

    {
        std::int64_t  li64     = 0;
        std::uint64_t lui64    = 0;

        Result += Serializer<std::int64_t>::deserialize(inStream, li64);
        Result += Serializer<std::uint64_t>::deserialize(inStream, lui64);

        assert(li64 == i64);
        assert(lui64== ui64);
    }

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializeFloats(std::istream& inStream)
{
    std::size_t Result = 0;

    float   lf32    = 0.0f;
    double  ld64    = 0.0;

    Result += Serializer<float>::deserialize(inStream, lf32);
    Result += Serializer<double>::deserialize(inStream, ld64);

    assert(lf32 == f32);
    assert(ld64== d64);

    return Result;
}
//-----------------------------------------------------------------------------
