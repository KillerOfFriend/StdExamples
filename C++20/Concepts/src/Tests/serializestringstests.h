#ifndef SERIALIZESTRINGSTESTS_H
#define SERIALIZESTRINGSTESTS_H

#include <cstddef>
#include <ostream>

//-----------------------------------------------------------------------------
namespace tests
{
    std::size_t SerializeString(std::ostream& inStream);
    std::size_t SerializeWString(std::ostream& inStream);
    std::size_t SerializeU8String(std::ostream& inStream);
    std::size_t SerializeU16String(std::ostream& inStream);
    std::size_t SerializeU32String(std::ostream& inStream);

    std::size_t DeSerializeString(std::istream& inStream);
    std::size_t DeSerializeWString(std::istream& inStream);
    std::size_t DeSerializeU8String(std::istream& inStream);
    std::size_t DeSerializeU16String(std::istream& inStream);
    std::size_t DeSerializeU32String(std::istream& inStream);
}
//-----------------------------------------------------------------------------

#endif // SERIALIZESTRINGSTESTS_H
