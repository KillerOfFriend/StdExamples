#ifndef SERIALIZERASSOCIATIVECONTAINER_HPP
#define SERIALIZERASSOCIATIVECONTAINER_HPP

#include "SerializerBase.hpp"
#include "ContainersConcepts.hpp"

//-----------------------------------------------------------------------------
/**
 * @brief The PairTypeConvert struct - Вспомогательная сущность определения типа данных контейнера
 * @tparam T - Сопостовляемый тип
 */
template<typename T>
struct PairTypeConvert
{
    using type = T;
};
//-----------------------------------------------------------------------------
/**
 * @brief The PairTypeConvert struct - Вспомогательная сущность определения типа данных контейнера
 * @tparam T - Сопостовляемый тип
 *
 * Для std::map — убираем const:
 */
template<typename T> requires StdPair<T>
struct PairTypeConvert<T>
{
    using type = std::pair<std::remove_const_t<typename T::first_type>, typename T::second_type>;
};
//-----------------------------------------------------------------------------
/**
 * @brief The Serializer class - Сериализатор ассоцииативных контейнеров
 * @tparam T - Сопостовляемый тип
 *
 * Поддерживается std::set, std::unordered_set, std::multiset, std::map,
 * std::unordered_map, std::multimap
 */
template<typename T> requires AssociativeStdContainer<T>
class Serializer<T>
{
public:

    Serializer() = default;
    ~Serializer() = default;

    static std::size_t serialize(std::ostream& inOStream, const T& inData);
    static std::size_t deserialize(std::istream& inIStream, T& outData);
};
//-----------------------------------------------------------------------------
template<typename T> requires AssociativeStdContainer<T>
std::size_t Serializer<T>::serialize(std::ostream &inOStream, const T& inData)
{
    const auto pos = inOStream.tellp();

    const std::uint32_t ItemsCount = inData.size();
    inOStream.write(reinterpret_cast<const char*>(&ItemsCount), sizeof(ItemsCount));

    if (ItemsCount > 0)
    {
        std::for_each(inData.cbegin(), inData.cend(), [&](const auto& item)
        { Serializer<typename T::value_type>::serialize(inOStream, item); });
    }

    return inOStream.tellp() - pos;
};
//-----------------------------------------------------------------------------
template<typename T> requires AssociativeStdContainer<T>
std::size_t Serializer<T>::deserialize(std::istream& inIStream, T& outData)
{
    using value_t = typename PairTypeConvert<typename T::value_type>::type;
    const auto pos = inIStream.tellg();
    outData.clear();

    std::uint32_t ItemsCount = 0;
    inIStream.read(reinterpret_cast<char*>(&ItemsCount), sizeof(ItemsCount));

    while (ItemsCount-- > 0)
    {
        value_t Item;
        Serializer<value_t>::deserialize(inIStream, Item);
        outData.insert(std::move(Item));
    }

    return inIStream.tellg() - pos;
}
//-----------------------------------------------------------------------------


#endif // SERIALIZERASSOCIATIVECONTAINER_HPP
