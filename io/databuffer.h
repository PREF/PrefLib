#ifndef PREFLIB_IO_DATABUFFER_H
#define PREFLIB_IO_DATABUFFER_H

#include <algorithm>
#include <cstdint>
#include <cctype>
#include "bt/btvm.h"

namespace PrefLib {
namespace IO {

class DataBuffer: public BTVMIO
{
    public:
        enum OpenMode { Read = 1, Write = 2, ReadWrite = Read | Write };

    public:
        DataBuffer(OpenMode openmode);
        ~DataBuffer();
        bool isReadable() const;
        bool isWritable() const;
        uint8_t at(uint64_t offset);

    public:
        virtual uint64_t size() const = 0;

    protected:
        virtual uint64_t read(uint8_t *buffer, uint64_t size) = 0;

    private:
        int _openmode;
};

} // namespace IO
} // namespace PrefLib

#endif // PREFLIB_IO_DATABUFFER_H
