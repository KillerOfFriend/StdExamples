// https://habr.com/ru/post/479462/

#include <cassert>
#include <sstream>
#include <fstream>

#include "Tests/serializetests.h"

//-----------------------------------------------------------------------------
std::size_t SerializeTests(std::ostream& inStream)
{
    std::size_t Result = 0;

    Result += tests::SerializeNumbers(inStream);
    Result += tests::SerializeStrings(inStream);
    Result += tests::SerializeContainers(inStream);

    return Result;
}
//-----------------------------------------------------------------------------
std::size_t DeSerializeTests(std::istream& inStream)
{
    std::size_t Result = 0;

    Result += tests::DeSerializeNumbers(inStream);
    Result += tests::DeSerializeStrings(inStream);
    Result += tests::DeSerializeContainers(inStream);

    return Result;
}
//-----------------------------------------------------------------------------
#define FILESTREAM
//-----------------------------------------------------------------------------
int main()
{  
#ifndef FILESTREAM
    std::stringstream Stream;
#else
    std::fstream Stream;
    Stream.open("StreamData.bin", std::ios::binary | std::ios::out | std::ios::in | std::ios::trunc);
#endif

    std::size_t SerDataSize = SerializeTests(Stream);       // Запускаем тест сериализации
    Stream.seekg(0); // Позицию чтения сбрасываем в начало потока
    std::size_t DeSerDataSize = DeSerializeTests(Stream);   // Запускаем тест десериализации

    assert(SerDataSize == DeSerDataSize); // Сколько записали столько и должны считать

    return 0;
}
//-----------------------------------------------------------------------------
