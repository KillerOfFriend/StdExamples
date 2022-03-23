#ifndef SERIALIZATION_TESTS_H
#define SERIALIZATION_TESTS_H

#include <iostream>

#include "serialization_iostream.hpp"

namespace tests
{
    void serializationArithmetic(serialization::serial_iostream& inStream);
    void serializationString(serialization::serial_iostream& inStream);
    // Sequence containers
    void serializationSequenceContainers(serialization::serial_iostream& inStream);
    void serializationStdArray(serialization::serial_iostream& inStream);
    void serializationStdVectory(serialization::serial_iostream& inStream);
    void serializationStdDeque(serialization::serial_iostream& inStream);
    void serializationStdForvardList(serialization::serial_iostream& inStream);
    void serializationStdList(serialization::serial_iostream& inStream);
    // Associative containers
    void serializationAssociativeContainers(serialization::serial_iostream& inStream);
    void serializationStdSet(serialization::serial_iostream& inStream);
    void serializationStdMap(serialization::serial_iostream& inStream);
    void serializationStdMultiSet(serialization::serial_iostream& inStream);
    void serializationStdMultiMap(serialization::serial_iostream& inStream);
    // Associative unordered containers
    void serializationStdUnorderedSet(serialization::serial_iostream& inStream);
    void serializationStdUnorderedMap(serialization::serial_iostream& inStream);
    void serializationStdUnorderedMultiSet(serialization::serial_iostream& inStream);
    void serializationStdUnorderedMultiMap(serialization::serial_iostream& inStream);
    //-------------------------------------------------------------------------
    void deserializationArithmetic(serialization::serial_iostream& inStream);
    void deserializationString(serialization::serial_iostream& inStream);
    // Sequence containers
    void deserializationSequenceContainers(serialization::serial_iostream& inStream);
    void deserializationStdArray(serialization::serial_iostream& inStream);
    void deserializationStdVectory(serialization::serial_iostream& inStream);
    void deserializationStdDeque(serialization::serial_iostream& inStream);
    void deserializationStdForvardList(serialization::serial_iostream& inStream);
    void deserializationStdList(serialization::serial_iostream& inStream);
    // Associative containers
    void deserializationAssociativeContainers(serialization::serial_iostream& inStream);
    void deserializationStdSet(serialization::serial_iostream& inStream);
    void deserializationStdMap(serialization::serial_iostream& inStream);
    void deserializationStdMultiSet(serialization::serial_iostream& inStream);
    void deserializationStdMultiMap(serialization::serial_iostream& inStream);
    // Associative unordered containers
    void deserializationStdUnorderedSet(serialization::serial_iostream& inStream);
    void deserializationStdUnorderedMap(serialization::serial_iostream& inStream);
    void deserializationStdUnorderedMultiSet(serialization::serial_iostream& inStream);
    void deserializationStdUnorderedMultiMap(serialization::serial_iostream& inStream);
}

#endif // SERIALIZATION_TESTS_H
