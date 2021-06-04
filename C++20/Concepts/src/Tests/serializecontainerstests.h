#ifndef SERIALIZECONTAINERSTESTS_H
#define SERIALIZECONTAINERSTESTS_H

#include <cstddef>
#include <ostream>

//-----------------------------------------------------------------------------
namespace tests
{
    // Последовательные
    std::size_t SerializList(std::ostream& inStream);
    std::size_t SerializVector(std::ostream& inStream);
    std::size_t SerializDeque(std::ostream& inStream);

    std::size_t DeSerializList(std::istream& inStream);
    std::size_t DeSerializVector(std::istream& inStream);
    std::size_t DeSerializDeque(std::istream& inStream);

    // Ассоциированые
    std::size_t SerializSet(std::ostream& inStream);
    std::size_t SerializUnorderedSet(std::ostream& inStream);
    std::size_t SerializMap(std::ostream& inStream);
    std::size_t SerializUnorderedMap(std::ostream& inStream);

    std::size_t DeSerializSet(std::istream& inStream);
    std::size_t DeSerializUnorderedSet(std::istream& inStream);
    std::size_t DeSerializMap(std::istream& inStream);
    std::size_t DeSerializUnorderedMap(std::istream& inStream);

    // Обобщения
    std::size_t SerializeSequenceContainers(std::ostream& inStream);
    std::size_t SerializeAssociativeContainers(std::ostream& inStream);

    std::size_t DeSerializeSequenceContainers(std::istream& inStream);
    std::size_t DeSerializeAssociativeContainers(std::istream& inStream);
}
//-----------------------------------------------------------------------------

#endif // SERIALIZECONTAINERSTESTS_H
