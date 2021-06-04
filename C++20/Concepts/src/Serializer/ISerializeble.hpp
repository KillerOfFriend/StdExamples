#ifndef ISERIALIZEBLE_HPP
#define ISERIALIZEBLE_HPP

#include <iostream>

//-----------------------------------------------------------------------------
/**
 * @brief The ISerializeble class - Интерфейс сериализуемого класса
 */
class ISerializeble
{
public:

    ISerializeble() = default;
    virtual ~ISerializeble() = default;

    /**
     * @brief serialize - Метод сериализует класс в поток
     * @param inOStream - Выходной поток
     * @return Вернёт количество сериализованных байт
     */
    virtual std::size_t serialize(std::ostream& inOStream) const = 0;
    /**
     * @brief deserialize - Медот десериализует классс из потока
     * @param inOStream - Входной опток
     * @return Вернёт количество десериализованных байт
     */
    virtual std::size_t deserialize(std::istream& inOStream) = 0;

};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& inOStream, const ISerializeble& inData)
{
    inData.serialize(inOStream);
    return inOStream;
}
//-----------------------------------------------------------------------------
inline std::istream& operator>>(std::istream& inIStream, ISerializeble& inData)
{
    inData.deserialize(inIStream);
    return inIStream;
}
//-----------------------------------------------------------------------------
#endif // ISERIALIZEBLE_HPP
