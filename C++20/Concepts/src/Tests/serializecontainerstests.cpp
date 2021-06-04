#include "serializecontainerstests.h"

#include <cassert>

#include <list>
#include <forward_list>
#include <vector>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

#include "Serializer/Serializer.hpp"

typedef std::int32_t    ser_std_key;
typedef std::string     ser_std_type;

typedef std::list<ser_std_type>         ser_list;
typedef std::forward_list<ser_std_type> ser_flist;
typedef std::vector<ser_std_type>       ser_vector;
typedef std::deque<ser_std_type>        ser_deque;

static const ser_list   gList   = { "List0", "List1","List2","List3","List4" };
static const ser_flist  gFList  = { "ForwardList0","ForwardList1","ForwardList2","ForwardList3","ForwardList4" };
static const ser_vector gVector = { "Vector0","Vector1","Vector2","Vector3","Vector4" };
static const ser_deque  gDeque  = { "gDeque0", "gDeque1", "gDeque2", "gDeque3", "gDeque4" };

typedef std::set<ser_std_type> ser_set;
typedef std::unordered_set<ser_std_type> ser_uset;
typedef std::map<ser_std_key, ser_std_type> ser_map;
typedef std::unordered_map<ser_std_key, ser_std_type> ser_umap;

static const ser_set    gSet    = { "Set0", "Set1","Set2","Set3","Set4" };
static const ser_uset   gUSet   = { "USet0", "USet1","USet2","USet3","USet4" };
static const ser_map    gMap    = { {0, "Map0"}, {1, "Map1"}, {2, "Map2"}, {3, "Map3"}, {4, "Map4"} };
static const ser_umap   gUMap   = { {0, "UMap0"}, {1, "UMap1"}, {2, "UMap2"}, {3, "UMap3"}, {4, "UMap4"} };

//-----------------------------------------------------------------------------
// Последовательные
//-----------------------------------------------------------------------------
std::size_t tests::SerializList(std::ostream& inStream)
{
    return Serializer<ser_list>::serialize(inStream, gList);
}
//-----------------------------------------------------------------------------
std::size_t tests::SerializVector(std::ostream& inStream)
{
    return Serializer<ser_vector>::serialize(inStream, gVector);
}
//-----------------------------------------------------------------------------
std::size_t tests::SerializDeque(std::ostream& inStream)
{
    return Serializer<ser_deque>::serialize(inStream, gDeque);
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializList(std::istream& inStream)
{
    ser_list List;

    std::size_t Result = Serializer<ser_list>::deserialize(inStream, List);
    assert(List == gList);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializVector(std::istream& inStream)
{
    ser_vector Vector;

    std::size_t Result = Serializer<ser_vector>::deserialize(inStream, Vector);
    assert(Vector == gVector);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializDeque(std::istream& inStream)
{
    ser_deque Deque;

    std::size_t Result = Serializer<ser_deque>::deserialize(inStream, Deque);
    assert(Deque == gDeque);

    return Result;
}
//-----------------------------------------------------------------------------
// Ассоциированые
//-----------------------------------------------------------------------------
std::size_t tests::SerializSet(std::ostream& inStream)
{
    return Serializer<ser_set>::serialize(inStream, gSet);
}
//-----------------------------------------------------------------------------
std::size_t tests::SerializUnorderedSet(std::ostream& inStream)
{
    return Serializer<ser_uset>::serialize(inStream, gUSet);
}
//-----------------------------------------------------------------------------
std::size_t tests::SerializMap(std::ostream& inStream)
{
    return Serializer<ser_map>::serialize(inStream, gMap);
}
//-----------------------------------------------------------------------------
std::size_t tests::SerializUnorderedMap(std::ostream& inStream)
{
    return Serializer<ser_umap>::serialize(inStream, gUMap);
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializSet(std::istream& inStream)
{
    ser_set Set;

    std::size_t Result = Serializer<ser_set>::deserialize(inStream, Set);
    assert(Set == gSet);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializUnorderedSet(std::istream& inStream)
{
    ser_uset USet;

    std::size_t Result = Serializer<ser_uset>::deserialize(inStream, USet);
    assert(USet == gUSet);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializMap(std::istream& inStream)
{
    ser_map Map;

    std::size_t Result = Serializer<ser_map>::deserialize(inStream, Map);
    assert(Map == gMap);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializUnorderedMap(std::istream& inStream)
{
    ser_umap UMap;

    std::size_t Result = Serializer<ser_umap>::deserialize(inStream, UMap);
    assert(UMap == gUMap);

    return Result;
}
//-----------------------------------------------------------------------------
// Обобщения
//-----------------------------------------------------------------------------
std::size_t tests::SerializeSequenceContainers(std::ostream& inStream)
{   // Сериализация стандартных последовательных контейнеров
    std::size_t Result = 0;

    Result += SerializList(inStream);
    Result += SerializVector(inStream);
    Result += SerializDeque(inStream);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::SerializeAssociativeContainers(std::ostream& inStream)
{   // Сериализация стандартных ассоциотивных контейнеров
    std::size_t Result = 0;

    Result += SerializSet(inStream);
    Result += SerializUnorderedSet(inStream);
    Result += SerializMap(inStream);
    Result += SerializUnorderedMap(inStream);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializeSequenceContainers(std::istream& inStream)
{   // Десериализация стандартных последовательных контейнеров
    std::size_t Result = 0;

    Result += DeSerializList(inStream);
    Result += DeSerializVector(inStream);
    Result += DeSerializDeque(inStream);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t tests::DeSerializeAssociativeContainers(std::istream& inStream)
{ // Десериализация стандартных ассоциотивных контейнеров
    std::size_t Result = 0;

    Result += DeSerializSet(inStream);
    Result += DeSerializUnorderedSet(inStream);
    Result += DeSerializMap(inStream);
    Result += DeSerializUnorderedMap(inStream);

    return Result;
}
//-----------------------------------------------------------------------------
