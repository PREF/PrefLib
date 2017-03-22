#include "databuffer.h"
#include <cstring>

namespace PrefLib {
namespace IO {

DataBuffer::DataBuffer(OpenMode openmode): _openmode(openmode)
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

unsigned char DataBuffer::at(uint64_t offset)
{
    unsigned char ch = '\0';
    this->read(offset, &ch, 1);
    return ch;
}

int64_t DataBuffer::indexOf(const char *s, uint64_t startoffset)
{
    uint64_t len = strlen(s);
    char* cmpstring = new char[len + 1];
    cmpstring[len] = '\0';

    for(uint64_t i = startoffset; i < this->length(); i++)
    {
        char ch = static_cast<char>(this->at(i));

        if(ch == s[0])
        {
            this->read(i, reinterpret_cast<unsigned char*>(cmpstring), len);

            if(!strcmp(s, cmpstring))
                return static_cast<int64_t>(i);
        }
    }

    return -1;
}

uint64_t DataBuffer::readString(uint64_t offset, char **data, uint64_t maxlen)
{
    uint64_t len = 0, bufflen = this->length();

    if(!maxlen)
        maxlen = bufflen;

    for(uint64_t i = 0; i < maxlen; i++)
    {
        uint64_t curroffset = offset + i;

        if(curroffset >= bufflen)
            break;

        unsigned char ch = this->at(curroffset);

        if(!ch || (ch > 0x7F))
            break;

        len++;
    }

    *data = new char[len + 1];
    (*data)[len] = '\0';

    return this->read(offset, reinterpret_cast<unsigned char*>(*data), len);
}

uint64_t DataBuffer::readLine(uint64_t offset, char **data)
{
    uint64_t len = 0;

    for(uint64_t i = offset; i < this->length(); i++)
    {
        unsigned char ch = this->at(i);

        if(ch == '\n' || ch == '\r')
            break;

        len++;
    }

    *data = new char[len + 1];
    (*data)[len] = '\0';

    return this->read(offset, reinterpret_cast<unsigned char*>(*data), len);
}

/*FIXME:
DataValue DataBuffer::readType(uint64_t offset, DataType::Type datatype)
{
    DataValue dv = 0;

    this->read(offset, &dv, DataType::sizeOf(datatype));
    dv.castTo(datatype);
    return dv;
}
*/

void DataBuffer::copyTo(DataBuffer *destbuffer, uint64_t startoffset, uint64_t endoffset)
{
    if(!endoffset)
        endoffset = this->length();

    uint64_t len = endoffset - startoffset;
    unsigned char* data = new unsigned char[len];

    this->read(startoffset, data, len);
    destbuffer->write(0, data, len);

    delete[] data;
}

} // namespace IO
} // namespace PrefLib

