#ifndef SERIALIZETESTS_H
#define SERIALIZETESTS_H

#include <cstddef>
#include <iostream>

//-----------------------------------------------------------------------------
namespace tests
{
    std::size_t SerializeNumbers(std::ostream& inStream);
    std::size_t SerializeStrings(std::ostream& inStream);
    std::size_t SerializeContainers(std::ostream& inStream);

    std::size_t DeSerializeNumbers(std::istream& inStream);
    std::size_t DeSerializeStrings(std::istream& inStream);
    std::size_t DeSerializeContainers(std::istream& inStream);
}
//-----------------------------------------------------------------------------

#endif // SERIALIZETESTS_H
