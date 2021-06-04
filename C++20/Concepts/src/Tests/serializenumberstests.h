#ifndef SERIALIZENUMBERSTESTS_H
#define SERIALIZENUMBERSTESTS_H

#include <cstddef>
#include <iostream>

//-----------------------------------------------------------------------------
namespace tests
{
    std::size_t SerializeInt(std::ostream& inStream);
    std::size_t SerializeFloats(std::ostream& inStream);

    std::size_t DeSerializeInt(std::istream& inStream);
    std::size_t DeSerializeFloats(std::istream& inStream);
}
//-----------------------------------------------------------------------------

#endif // SERIALIZENUMBERSTESTS_H
