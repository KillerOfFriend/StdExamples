#ifndef SERIALIZERBASE_H
#define SERIALIZERBASE_H

#include <cstddef>
#include <iostream>

//-----------------------------------------------------------------------------
// Базовые типы
//-----------------------------------------------------------------------------
/**
 * @brief The Serializer class - Класс, сериализатор
 * @tparam T - Тип cериализуемых данных
 */
template<typename T>
class Serializer
{
public:

    Serializer() = default;
    ~Serializer() = default;

    static std::size_t serialize(std::ostream& inOStream, const T& inData);
    static std::size_t deserialize(std::istream& inIStream, T& outData);
};
//-----------------------------------------------------------------------------
template<typename T>
std::size_t Serializer<T>::serialize(std::ostream &inOStream, const T& inData)
{
    const auto pos = inOStream.tellp();
    inOStream.write(reinterpret_cast<const char*>(&inData), sizeof(inData));
    return inOStream.tellp() - pos;
}
//-----------------------------------------------------------------------------
template<typename T>
std::size_t Serializer<T>::deserialize(std::istream& inIStream, T& outData)
{
    const auto pos = inIStream.tellg();
    inIStream.read(reinterpret_cast<char*>(&outData), sizeof(outData));
    return inIStream.tellg() - pos;
}
//-----------------------------------------------------------------------------

#endif // SERIALIZERBASE_H
