#include <chrono>
#include <iomanip>
#include <iostream>

#include "serialization.hpp"
#include "serialization_tests.h"

//-----------------------------------------------------------------------------
void start_tests(const size_t inReserveSize)
{
    std::vector<char> ByteBuffer;
    ByteBuffer.reserve(inReserveSize);

    serialization::vector_streambuf<char> StreamBuffer(ByteBuffer);
    serialization::serial_iostream Stream(&StreamBuffer);

    tests::serializationArithmetic(Stream);
    tests::serializationString(Stream);
    tests::serializationSequenceContainers(Stream);
    tests::serializationAssociativeContainers(Stream);

    tests::deserializationArithmetic(Stream);
    tests::deserializationString(Stream);
    tests::deserializationSequenceContainers(Stream);
    tests::deserializationAssociativeContainers(Stream);
}
//-----------------------------------------------------------------------------
int main()
{   
    //---
    auto start = std::chrono::high_resolution_clock::now();
    start_tests(1);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mks" << std::endl;
    //---
    start = std::chrono::high_resolution_clock::now();
    start_tests(1024);
    end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mks" << std::endl;
    //---
    start = std::chrono::high_resolution_clock::now();
    start_tests(2048);
    end = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mks" << std::endl;

    std::cout << "Hello World!" << std::endl;
    return 0;
}
//-----------------------------------------------------------------------------
