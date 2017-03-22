#ifndef PREFLIB_IO_DATABUFFER_H
#define PREFLIB_IO_DATABUFFER_H

#include <algorithm>
#include <cstdint>
#include <cctype>

namespace PrefLib {
namespace IO {

class DataBuffer
{
    public:
        enum OpenMode { Read = 1, Write = 2, ReadWrite = Read | Write };

    public:
        DataBuffer(OpenMode openmode);
        ~DataBuffer();
        bool isReadable() const;
        bool isWritable() const;

    public:
        unsigned char at(uint64_t offset);
        int64_t indexOf(const char* s, uint64_t startoffset = 0);
        uint64_t readString(uint64_t offset, char** data, uint64_t maxlen = 0);
        uint64_t readLine(uint64_t offset, char** data);
        //FIXME: DataValue readType(uint64_t offset, DataType::Type datatype);
        void copyTo(DataBuffer* destbuffer, uint64_t startoffset = 0, uint64_t endoffset = 0);

    public: /* Abstract Methods */
        virtual uint64_t length() const = 0;
        virtual uint64_t read(uint64_t offset, unsigned char* data, uint64_t len) = 0;
        virtual uint64_t write(uint64_t offset, const unsigned char* data, uint64_t len) = 0;

    private:
        int _openmode;
};

} // namespace IO
} // namespace PrefLib

#endif // PREFLIB_IO_DATABUFFER_H
