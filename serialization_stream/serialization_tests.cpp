#include "serialization_tests.h"

#include <limits>
#include <cassert>
#include <cstdint>
#include <iostream>

#include <set>
#include <map>
#include <array>
#include <deque>
#include <list>
#include <vector>
#include <string>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>

#include "serialization_types.hpp"

//-----------------------------------------------------------------------------
template <typename T>
struct numericVals
{
public:
    numericVals() :
        minVal(std::numeric_limits<T>::min()),
        maxVal(std::numeric_limits<T>::max())
    {};

    numericVals(const T& inMin, const T& inMax) :
        minVal(inMin),
        maxVal(inMax)
    {};

    ~numericVals() = default;

    T minVal = {};
    T maxVal = {};
};
//-----------------------------------------------------------------------------
template <typename T>
serialization::serial_iostream& operator<<(serialization::serial_iostream& os, const numericVals<T>& dt)
{
    os << dt.minVal << dt.maxVal;
    return os;
}
//-----------------------------------------------------------------------------
template <typename T>
serialization::serial_iostream& operator>>(serialization::serial_iostream& os, numericVals<T>& dt)
{
    os >> dt.minVal >> dt.maxVal;
    return os;
}
//-----------------------------------------------------------------------------
template <typename T>
constexpr bool operator==(const numericVals<T>& lhs, const numericVals<T>& rhs)
{
    return lhs.minVal == rhs.minVal && lhs.maxVal == rhs.maxVal;
}
//-----------------------------------------------------------------------------

static const numericVals<bool>     i_b;

static const numericVals<int8_t>   i_i8;
static const numericVals<uint8_t>  i_ui8;

static const numericVals<int16_t>  i_i16;
static const numericVals<uint16_t> i_ui16;

static const numericVals<int32_t>  i_i32;
static const numericVals<uint32_t> i_ui32;

static const numericVals<int64_t>  i_i64;
static const numericVals<uint64_t> i_ui64;

static const numericVals<float>    i_f4;
static const numericVals<double>   i_d8;

static const std::u8string         i_u8s = u8"UTF8 текст. 1234567890";
static const std::u16string        i_u16s = u"UTF16 текст. 1234567890";
static const std::u32string        i_u32s = U"UTF32 текст. 1234567890";

static const std::array<std::string, 3>     i_arrstr = {"Первый", "Второй", "Третий"};
static const std::vector<std::string>       i_vecstr = {"Четвёртый", "Пятый", "Шестой"};
static const std::deque<std::string>        i_deqstr = {"Седьмой", "Восьмой", "Девятый"};
static const std::forward_list<std::string> i_flsstr = {"Десятый", "Одинадцатый", "Двенадцатый"};
static const std::list<std::string>         i_lststr = {"Тренадцатый", "Четырнадцатый", "Пятнадцатый"};

static const std::array<int32_t, 3>         i_arrint = {1,2,3};
static const std::vector<int32_t>           i_vecint = {4,5,6};
static const std::deque<int32_t>            i_deqint = {7,8,9};
static const std::forward_list<int32_t>     i_flsint = {10,11,12};
static const std::list<int32_t>             i_lstint = {13,14,15};

static const std::set<std::string>              i_setstr = {"Первый", "Второй", "Третий"};
static const std::map<char, std::string>        i_mapstr = {{'1', "Четвёртый"}, {'2', "Пятый"}, {'3', "Шестой"}};
static const std::multiset<std::string>         i_msetstr = {"Седьмой", "Седьмой", "Восьмой", "Восьмой", "Девятый", "Девятый"};
static const std::multimap<char, std::string>   i_mmapstr = {{'4', "Десятый"}, {'4', "Десятый"}, {'5', "Одинадцатый"}, {'5', "Одинадцатый"}, {'6', "Двенадцатый"}, {'6', "Двенадцатый"}};

static const std::unordered_set<std::string>              i_hsetstr = {"Первый", "Второй", "Третий"};
static const std::unordered_map<char, std::string>        i_hmapstr = {{'1', "Четвёртый"}, {'2', "Пятый"}, {'3', "Шестой"}};
static const std::unordered_multiset<std::string>         i_hmsetstr = {"Седьмой", "Седьмой", "Восьмой", "Восьмой", "Девятый", "Девятый"};
static const std::unordered_multimap<char, std::string>   i_hmmapstr = {{'4', "Десятый"}, {'4', "Десятый"}, {'5', "Одинадцатый"}, {'5', "Одинадцатый"}, {'6', "Двенадцатый"}, {'6', "Двенадцатый"}};

static const std::set<int32_t>                  i_setint = {1,2,3};
static const std::map<int32_t, int32_t>         i_mapint = {{1, 4}, {2, 5}, {3, 6}};
static const std::multiset<int32_t>             i_msetint = {7,7,8,8,9,9};
static const std::multimap<int32_t, int32_t>    i_mmapint = {{4, 10}, {4, 10}, {5, 11}, {5, 11}, {6, 12}, {6, 12}};

static const std::unordered_set<int32_t>                  i_hsetint = {1,2,3};
static const std::unordered_map<int32_t, int32_t>         i_hmapint = {{1, 4}, {2, 5}, {3, 6}};
static const std::unordered_multiset<int32_t>             i_hmsetint = {7,7,8,8,9,9};
static const std::unordered_multimap<int32_t, int32_t>    i_hmmapint = {{4, 10}, {4, 10}, {5, 11}, {5, 11}, {6, 12}, {6, 12}};

//-----------------------------------------------------------------------------
void tests::serializationArithmetic(serialization::serial_iostream& inStream)
{
    inStream << i_b << i_i8 << i_ui8 << i_i16 << i_ui16 << i_i32 << i_ui32 << i_i64 << i_ui64 << i_f4 << i_d8;
    assert(inStream);
}
//-----------------------------------------------------------------------------
void tests::serializationString(serialization::serial_iostream& inStream)
{
    inStream << i_u8s << i_u16s << i_u32s;
    assert(inStream);
}
//-----------------------------------------------------------------------------
void tests::serializationSequenceContainers(serialization::serial_iostream& inStream)
{
    serializationStdArray(inStream);
    serializationStdVectory(inStream);
    serializationStdDeque(inStream);
    serializationStdForvardList(inStream);
    serializationStdList(inStream);
}
//-----------------------------------------------------------------------------
void tests::serializationStdArray(serialization::serial_iostream& inStream)
{
    inStream << i_arrstr << i_arrint;
    assert(inStream);
}
//-----------------------------------------------------------------------------
void tests::serializationStdVectory(serialization::serial_iostream& inStream)
{
    inStream << i_vecstr << i_vecint;
    assert(inStream);
}
//-----------------------------------------------------------------------------
void tests::serializationStdDeque(serialization::serial_iostream& inStream)
{
    inStream << i_deqstr << i_deqint;
    assert(inStream);
}
//-----------------------------------------------------------------------------
void tests::serializationStdForvardList(serialization::serial_iostream& inStream)
{
    inStream << i_flsstr << i_flsint;
    assert(inStream);
}
//-----------------------------------------------------------------------------
void tests::serializationStdList(serialization::serial_iostream& inStream)
{
    inStream << i_lststr << i_lstint;
    assert(inStream);
}
//-----------------------------------------------------------------------------
void tests::serializationAssociativeContainers(serialization::serial_iostream& inStream)
{
    serializationStdSet(inStream);
    serializationStdMap(inStream);
    serializationStdMultiSet(inStream);
    serializationStdMultiMap(inStream);

    serializationStdUnorderedSet(inStream);
    serializationStdUnorderedMap(inStream);
    serializationStdUnorderedMultiSet(inStream);
    serializationStdUnorderedMultiMap(inStream);
}
//-----------------------------------------------------------------------------
void tests::serializationStdSet(serialization::serial_iostream& inStream)
{
    inStream << i_setstr << i_setint;
    assert(inStream);
}
//-----------------------------------------------------------------------------
void tests::serializationStdMap(serialization::serial_iostream& inStream)
{
    inStream << i_mapstr << i_mapint;
    assert(inStream);
}
//-----------------------------------------------------------------------------
void tests::serializationStdMultiSet(serialization::serial_iostream& inStream)
{
    inStream << i_msetstr << i_msetint;
    assert(inStream);
}
//-----------------------------------------------------------------------------
void tests::serializationStdMultiMap(serialization::serial_iostream& inStream)
{
    inStream << i_mmapstr << i_mmapint;
    assert(inStream);
}
//-----------------------------------------------------------------------------
void tests::serializationStdUnorderedSet(serialization::serial_iostream& inStream)
{
    inStream << i_hsetstr << i_hsetint;
    assert(inStream);
}
//-----------------------------------------------------------------------------
void tests::serializationStdUnorderedMap(serialization::serial_iostream& inStream)
{
    inStream << i_hmapstr << i_hmapint;
    assert(inStream);
}
//-----------------------------------------------------------------------------
void tests::serializationStdUnorderedMultiSet(serialization::serial_iostream& inStream)
{
    inStream << i_hmsetstr << i_hmsetint;
    assert(inStream);
}
//-----------------------------------------------------------------------------
void tests::serializationStdUnorderedMultiMap(serialization::serial_iostream& inStream)
{
    inStream << i_hmmapstr << i_hmmapint;
    assert(inStream);
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void tests::deserializationArithmetic(serialization::serial_iostream& inStream)
{
    numericVals<bool>       o_b     = {0, 0};

    numericVals<int8_t>     o_i8    = {0, 0};
    numericVals<uint8_t>    o_ui8   = {0, 0};

    numericVals<int16_t>    o_i16   = {0, 0};
    numericVals<uint16_t>   o_ui16  = {0, 0};

    numericVals<int32_t>    o_i32   = {0, 0};
    numericVals<uint32_t>   o_ui32  = {0, 0};

    numericVals<int64_t>    o_i64   = {0, 0};
    numericVals<uint64_t>   o_ui64  = {0, 0};

    numericVals<float>      o_f4    = {0.0, 0.0};
    numericVals<double>     o_d8    = {0.0, 0.0};

    inStream >> o_b >> o_i8 >> o_ui8 >> o_i16 >> o_ui16 >> o_i32 >> o_ui32 >> o_i64 >> o_ui64 >> o_f4 >> o_d8;
    assert(inStream);

    assert(i_b == o_b);
    assert(i_i8 == o_i8);
    assert(i_ui8 == o_ui8);
    assert(i_i16 == o_i16);
    assert(i_ui16 == o_ui16);
    assert(i_i32 == o_i32);
    assert(i_ui32 == o_ui32);
    assert(i_i64 == o_i64);
    assert(i_ui64 == o_ui64);
    assert(i_f4 == o_f4);
    assert(i_d8 == o_d8);
}
//-----------------------------------------------------------------------------
void tests::deserializationString(serialization::serial_iostream& inStream)
{
    std::u8string   o_u8s;
    std::u16string  o_u16s;
    std::u32string  o_u32s;

    inStream >> o_u8s >> o_u16s >> o_u32s;
    assert(inStream);

    assert(i_u8s == o_u8s);
    assert(i_u16s == o_u16s);
    assert(i_u32s == o_u32s);
}
//-----------------------------------------------------------------------------
void tests::deserializationSequenceContainers(serialization::serial_iostream& inStream)
{
    deserializationStdArray(inStream);
    deserializationStdVectory(inStream);
    deserializationStdDeque(inStream);
    deserializationStdForvardList(inStream);
    deserializationStdList(inStream);
}
//-----------------------------------------------------------------------------
void tests::deserializationStdArray(serialization::serial_iostream& inStream)
{
    std::array<std::string, 3> o_arrstr;
    std::array<int32_t, 3> o_arrint;

    inStream >> o_arrstr >> o_arrint;
    assert(inStream);

    assert(i_arrstr == o_arrstr);
    assert(i_arrint == o_arrint);
}
//-----------------------------------------------------------------------------
void tests::deserializationStdVectory(serialization::serial_iostream& inStream)
{
    std::vector<std::string> o_vecstr;
    std::vector<int32_t> o_vecint;

    inStream >> o_vecstr >> o_vecint;
    assert(inStream);

    assert(i_vecstr == o_vecstr);
    assert(i_vecint == o_vecint);
}
//-----------------------------------------------------------------------------
void tests::deserializationStdDeque(serialization::serial_iostream& inStream)
{
    std::deque<std::string> o_deqstr;
    std::deque<int32_t> o_deqint;

    inStream >> o_deqstr >> o_deqint;
    assert(inStream);

    assert(i_deqstr == o_deqstr);
    assert(i_deqint == o_deqint);
}
//-----------------------------------------------------------------------------
void tests::deserializationStdForvardList(serialization::serial_iostream& inStream)
{
    std::forward_list<std::string> o_flsstr;
    std::forward_list<int32_t> o_flsint;

    inStream >> o_flsstr >> o_flsint;
    assert(inStream);

    assert(i_flsstr == o_flsstr);
    assert(i_flsint == o_flsint);
}
//-----------------------------------------------------------------------------
void tests::deserializationStdList(serialization::serial_iostream& inStream)
{
    std::list<std::string> o_lststr;
    std::list<int32_t> o_lstint;

    inStream >> o_lststr >> o_lstint;
    assert(inStream);

    assert(i_lststr == o_lststr);
    assert(i_lstint == o_lstint);
}
//-----------------------------------------------------------------------------
void tests::deserializationAssociativeContainers(serialization::serial_iostream& inStream)
{
    deserializationStdSet(inStream);
    deserializationStdMap(inStream);
    deserializationStdMultiSet(inStream);
    deserializationStdMultiMap(inStream);

    deserializationStdUnorderedSet(inStream);
    deserializationStdUnorderedMap(inStream);
    deserializationStdUnorderedMultiSet(inStream);
    deserializationStdUnorderedMultiMap(inStream);
}
//-----------------------------------------------------------------------------
void tests::deserializationStdSet(serialization::serial_iostream& inStream)
{
    std::set<std::string>              o_setstr;
    std::set<int32_t>                  o_setint;

    inStream >> o_setstr >> o_setint;
    assert(inStream);

    assert(i_setstr == o_setstr);
    assert(i_setint == o_setint);
}
//-----------------------------------------------------------------------------
void tests::deserializationStdMap(serialization::serial_iostream& inStream)
{
    std::map<char, std::string>        o_mapstr;
    std::map<int32_t, int32_t>         o_mapint;

    inStream >> o_mapstr >> o_mapint;
    assert(inStream);

    assert(i_mapstr == o_mapstr);
    assert(i_mapint == o_mapint);
}
//-----------------------------------------------------------------------------
void tests::deserializationStdMultiSet(serialization::serial_iostream& inStream)
{
    std::multiset<std::string>         o_msetstr;
    std::multiset<int32_t>             o_msetint;

    inStream >> o_msetstr >> o_msetint;
    assert(inStream);

    assert(i_msetstr == o_msetstr);
    assert(i_msetint == o_msetint);
}
//-----------------------------------------------------------------------------
void tests::deserializationStdMultiMap(serialization::serial_iostream& inStream)
{
    std::multimap<char, std::string>   o_mmapstr;
    std::multimap<int32_t, int32_t>    o_mmapint;

    inStream >> o_mmapstr >> o_mmapint;
    assert(inStream);

    assert(i_mmapstr == o_mmapstr);
    assert(i_mmapint == o_mmapint);
}
//-----------------------------------------------------------------------------
void tests::deserializationStdUnorderedSet(serialization::serial_iostream& inStream)
{
    std::unordered_set<std::string>              o_hsetstr;
    std::unordered_set<int32_t>                  o_hsetint;

    inStream >> o_hsetstr >> o_hsetint;
    assert(inStream);

    assert(i_hsetstr == o_hsetstr);
    assert(i_hsetint == o_hsetint);
}
//-----------------------------------------------------------------------------
void tests::deserializationStdUnorderedMap(serialization::serial_iostream& inStream)
{
    std::unordered_map<char, std::string>        o_hmapstr;
    std::unordered_map<int32_t, int32_t>         o_hmapint;

    inStream >> o_hmapstr >> o_hmapint;
    assert(inStream);

    assert(i_hmapstr == o_hmapstr);
    assert(i_hmapint == o_hmapint);
}
//-----------------------------------------------------------------------------
void tests::deserializationStdUnorderedMultiSet(serialization::serial_iostream& inStream)
{
    std::unordered_multiset<std::string>         o_hmsetstr;
    std::unordered_multiset<int32_t>             o_hmsetint;

    inStream >> o_hmsetstr >> o_hmsetint;
    assert(inStream);

    assert(i_hmsetstr == o_hmsetstr);
    assert(i_hmsetint == o_hmsetint);
}
//-----------------------------------------------------------------------------
void tests::deserializationStdUnorderedMultiMap(serialization::serial_iostream& inStream)
{
    std::unordered_multimap<char, std::string>   o_hmmapstr;
    std::unordered_multimap<int32_t, int32_t>    o_hmmapint;

    inStream >> o_hmmapstr >> o_hmmapint;
    assert(inStream);

    assert(i_hmmapstr == o_hmmapstr);
    assert(i_hmmapint == o_hmmapint);
}
//-----------------------------------------------------------------------------
