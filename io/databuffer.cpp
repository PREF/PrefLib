#include "databuffer.h"
#include <cstring>

namespace PrefLib {
namespace IO {

DataBuffer::DataBuffer(OpenMode openmode): BTVMIO(), _openmode(openmode)
{
}

DataBuffer::~DataBuffer()
{

}

bool DataBuffer::isReadable() const
{
    return this->_openmode & OpenMode::Read;
}

bool DataBuffer::isWritable() const
{
    return this->_openmode & OpenMode::Write;
}

uint8_t DataBuffer::at(uint64_t offset)
{
    IO_NoSeek(this);

    uint8_t b = 0;

    this->seek(offset);
    this->readData(&b, 1);
    return b;
}

} // namespace IO
} // namespace PrefLib

