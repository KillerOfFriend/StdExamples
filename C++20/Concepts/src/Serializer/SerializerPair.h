#ifndef SERIALIZERPAIR_H
#define SERIALIZERPAIR_H

#include "SerializerBase.hpp"
#include "ContainersConcepts.hpp"

//-----------------------------------------------------------------------------
/**
 * @brief The Serializer class - Сериализатор стандартной пары
 * @tparam T - Сопостовляемый тип
 */
template<typename T> requires StdPair<T>
class Serializer<T>
{
public:

    Serializer() = default;
    ~Serializer() = default;

    static std::size_t serialize(std::ostream& inOStream, const T& inData);
    static std::size_t deserialize(std::istream& inIStream, T& outData);
};
//-----------------------------------------------------------------------------
template<typename T> requires StdPair<T>
std::size_t Serializer<T>::serialize(std::ostream &inOStream, const T& inData)
{
    const auto pos = inOStream.tellp();

    Serializer<typename T::first_type>::serialize(inOStream, inData.first);
    Serializer<typename T::second_type>::serialize(inOStream, inData.second);

    return inOStream.tellp() - pos;;
};
//-----------------------------------------------------------------------------
template<typename T> requires StdPair<T>
std::size_t Serializer<T>::deserialize(std::istream& inIStream, T& outData)
{
    const auto pos = inIStream.tellg();

    Serializer<typename T::first_type>::deserialize(inIStream, outData.first);
    Serializer<typename T::second_type>::deserialize(inIStream, outData.second);

    return inIStream.tellg() - pos;
}
//-----------------------------------------------------------------------------

#endif // SERIALIZERPAIR_H
