#ifndef SERIALIZERSEQUENCECONTAINER_HPP
#define SERIALIZERSEQUENCECONTAINER_HPP

#include "SerializerBase.hpp"
#include "ContainersConcepts.hpp"

//-----------------------------------------------------------------------------
/**
 * @brief The Serializer class - Сериализатор последовательных контейнеров
 * @tparam T - Сопостовляемый тип
 *
 * Поддерживается std::list, std::vector, std::deque
 */
template<typename T> requires SequenceStdContainer<T>
class Serializer<T>
{
public:

    Serializer() = default;
    ~Serializer() = default;

    static std::size_t serialize(std::ostream& inOStream, const T& inData);
    static std::size_t deserialize(std::istream& inIStream, T& outData);
};
//-----------------------------------------------------------------------------
template<typename T> requires SequenceStdContainer<T>
std::size_t Serializer<T>::serialize(std::ostream &inOStream, const T& inData)
{
    const auto pos = inOStream.tellp();

    const std::uint32_t ItemsCount = inData.size();
    inOStream.write(reinterpret_cast<const char*>(&ItemsCount), sizeof(ItemsCount));

    if (ItemsCount > 0)
    {
        std::for_each(inData.cbegin(), inData.cend(), [&](const auto& Item)
        { Serializer<typename T::value_type>::serialize(inOStream, Item); });
    }

    return inOStream.tellp() - pos;
};
//-----------------------------------------------------------------------------
template<typename T> requires SequenceStdContainer<T>
std::size_t Serializer<T>::deserialize(std::istream& inIStream, T& outData)
{
    using value_t = typename T::value_type;
    const auto pos = inIStream.tellg();
    outData.clear();

    std::uint32_t ItemsCount = 0;
    inIStream.read(reinterpret_cast<char*>(&ItemsCount), sizeof(ItemsCount));

    while (ItemsCount-- > 0)
    {
        value_t Item;
        Serializer<value_t>::deserialize(inIStream, Item);
        outData.emplace_back(std::move(Item));
    }

    return inIStream.tellg() - pos;
}
//-----------------------------------------------------------------------------

#endif // SERIALIZERSEQUENCECONTAINER_HPP
