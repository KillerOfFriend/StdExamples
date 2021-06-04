#ifndef SERIALIZERSERIALIZEBLE_HPP
#define SERIALIZERSERIALIZEBLE_HPP

#include "SerializerBase.hpp"
#include "ContainersConcepts.hpp"

//-----------------------------------------------------------------------------
/**
 * @brief The Serializer class - Сериализатор наследников от ISerializeble
 * @tparam T - Сопостовляемый тип
 */
template<typename T> requires SerializebleHeir<T>
class Serializer<T>
{
public:

    Serializer() = default;
    ~Serializer() = default;

    static std::size_t serialize(std::ostream& inOStream, const T& inData);
    static std::size_t deserialize(std::istream& inIStream, T& outData);
};
//-----------------------------------------------------------------------------
template<typename T> requires SerializebleHeir<T>
std::size_t Serializer<T>::serialize(std::ostream &inOStream, const T& inData)
{
    return inData.serialize(inOStream);
};
//-----------------------------------------------------------------------------
template<typename T> requires SerializebleHeir<T>
std::size_t Serializer<T>::deserialize(std::istream& inIStream, T& outData)
{
    return outData.deserialize(inIStream);
}
//-----------------------------------------------------------------------------

#endif // SERIALIZERSERIALIZEBLE_HPP
