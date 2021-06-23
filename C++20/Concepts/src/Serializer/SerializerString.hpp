#ifndef SERIALIZERSTRING_HPP
#define SERIALIZERSTRING_HPP

#include <memory>

#include "SerializerBase.hpp"
#include "ContainersConcepts.hpp"

//-----------------------------------------------------------------------------
/**
 * @brief The Serializer class - Сериализатор стандартных строк
 * @tparam T - Сопостовляемый тип
 */
template<StdString T>
class Serializer<T>
{
public:

    Serializer() = default;
    ~Serializer() = default;

    static std::size_t serialize(std::ostream& inOStream, const T& inData);
    static std::size_t deserialize(std::istream& inIStream, T& outData);
};
//-----------------------------------------------------------------------------
template<StdString T>
std::size_t Serializer<T>::serialize(std::ostream &inOStream, const T& inData)
{
    const auto pos = inOStream.tellp();

    const std::uint32_t Length = inData.size(); // Длинна в символах!
    inOStream.write(reinterpret_cast<const char*>(&Length), sizeof(Length));

    if (Length > 0)
        inOStream.write(reinterpret_cast<const char*>(inData.data()), Length * sizeof(typename T::value_type));

    return inOStream.tellp() - pos;
};
//-----------------------------------------------------------------------------
template<StdString T>
std::size_t Serializer<T>::deserialize(std::istream& inIStream, T& outData)
{
    const auto pos = inIStream.tellg();

    std::uint32_t Length = 0; // Длинна в символах!
    inIStream.read(reinterpret_cast<char*>(&Length), sizeof(Length));

    if (Length > 0)
    {
        std::unique_ptr<typename T::value_type[], std::default_delete<typename T::value_type[]>> Buff =
                std::make_unique<typename T::value_type[]>(Length);

        inIStream.read(reinterpret_cast<char*>(Buff.get()), Length * sizeof(typename T::value_type));

        outData.assign(Buff.get(), Length);
    }

    return inIStream.tellg() - pos;
}
//-----------------------------------------------------------------------------

#endif // SERIALIZERSTRING_HPP
