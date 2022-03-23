#ifndef SERIALIZATION_TYPES_HPP
#define SERIALIZATION_TYPES_HPP

#include <type_traits>

#include "serialization_tools.h"
#include "serialization_concepts.hpp"
#include "serialization_iostream.hpp"

//-----------------------------------------------------------------------------
template<typename T>
requires(std::is_pointer_v<T>)
serialization::serial_iostream& operator<<(serialization::serial_iostream& os, const T inVal)
{
    os << *inVal;
    return os;
}
//-----------------------------------------------------------------------------
template<typename T>
requires(std::is_pointer_v<T>)
serialization::serial_iostream& operator >> (serialization::serial_iostream& is, T inVal)
{
    is >> *inVal;
    return is;
}
//-----------------------------------------------------------------------------
template<typename T>
requires(std::is_arithmetic_v<T>)
serialization::serial_iostream& operator<<(serialization::serial_iostream& os, const T inVal)
{
    os.write(reinterpret_cast<const char*>(&inVal), sizeof(T));
    return os;
}
//-----------------------------------------------------------------------------
template<typename T>
requires(std::is_arithmetic_v<T>)
serialization::serial_iostream& operator >> (serialization::serial_iostream& is, T& inVal)
{
    is.read(reinterpret_cast<char*>(&inVal), sizeof(T));
    return is;
}
//-----------------------------------------------------------------------------
#include <string>
//-----------------------------------------------------------------------------
template<typename T>
requires(is_specialization_v<T, std::basic_string>)
serialization::serial_iostream& operator<<(serialization::serial_iostream& os, const T& inVal)
{
    const uint32_t strLength = inVal.length();
    os.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));

    if (strLength)
    {
        constexpr auto oneCharSize = sizeof(typename T::value_type);
        os.write(reinterpret_cast<const char*>(inVal.data()), strLength * oneCharSize);
    }
    return os;
}
//-----------------------------------------------------------------------------
template<typename T>
requires(is_specialization_v<T, std::basic_string>)
serialization::serial_iostream& operator >> (serialization::serial_iostream& is, T& inVal)
{
    inVal.clear();

    uint32_t strLength = 0;
    is.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));

    if (strLength)
    {
        constexpr auto oneCharSize = sizeof(typename T::value_type);
        inVal.assign(strLength, {});
        is.read(reinterpret_cast<char*>(inVal.data()), strLength * oneCharSize);
    }

    return is;
}
//-----------------------------------------------------------------------------
template<typename T>
requires(std_pair<T>)
serialization::serial_iostream& operator << (serialization::serial_iostream& os, const T& inVal)
{
    os << inVal.first << inVal.second;
    return os;
}
//-----------------------------------------------------------------------------
template<typename T>
requires(std_pair<T>)
serialization::serial_iostream& operator >> (serialization::serial_iostream& os, T& inVal)
{
    os >> inVal.first >> inVal.second;
    return os;
}
//-----------------------------------------------------------------------------
template<typename T>
requires(sequence_container<T> && !is_specialization_v<T, std::basic_string>)
serialization::serial_iostream& operator << (serialization::serial_iostream& os, const T& inVal)
{
    const uint32_t itemsCount = std::distance(inVal.begin(), inVal.end());
    os.write(reinterpret_cast<const char*>(&itemsCount), sizeof(itemsCount));

    for (const auto& Item : inVal)
        os << Item;

    return os;
}
//-----------------------------------------------------------------------------
#include "sequence_container_helpers.hpp"
template<typename T>
requires(sequence_container<T> && !is_specialization_v<T, std::basic_string>)
serialization::serial_iostream& operator >> (serialization::serial_iostream& is, T& inVal)
{
    uint32_t itemsCount = 0;
    is.read(reinterpret_cast<char*>(&itemsCount), sizeof(itemsCount));
    add_helper<T> helper(inVal);

    while(itemsCount--)
    {
        typename T::value_type Item = {};
        is >> Item;

        helper.add(std::move(Item));
    }

    helper.flush();
    return is;
}
//-----------------------------------------------------------------------------
template<typename T>
requires(associative_container<T>)
serialization::serial_iostream& operator << (serialization::serial_iostream& os, const T& inVal)
{
    const uint32_t itemsCount = std::distance(inVal.begin(), inVal.end());
    os.write(reinterpret_cast<const char*>(&itemsCount), sizeof(itemsCount));

    for (const auto& Item : inVal)
      os << Item;

    return os;
}
//-----------------------------------------------------------------------------
template<typename T>
requires(associative_container<T>)
serialization::serial_iostream& operator >> (serialization::serial_iostream& is, T& inVal)
{
    uint32_t itemsCount = 0;
    is.read(reinterpret_cast<char*>(&itemsCount), sizeof(itemsCount));

    while(itemsCount--)
    {
        non_const_container_val_t<T> Item = {};
        is >> Item;

        inVal.emplace(std::move(Item));
    }

    return is;
}
//-----------------------------------------------------------------------------
#endif // SERIALIZATION_TYPES_HPP
