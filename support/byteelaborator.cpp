#include "byteelaborator.h"

namespace PrefLib {
namespace Support {

const uint64_t ByteElaborator::MIN_LENGTH = 4;
const uint64_t ByteElaborator::MAX_LENGTH = 256;

ByteElaborator::ByteElaborator()
{

}

ByteElaborator::~ByteElaborator()
{

}

void ByteElaborator::countBytes(CountResult &result, IO::DataBuffer *databuffer, uint64_t startoffset, uint64_t endoffset, volatile bool *cancontinue)
{
    result.MaxByte = 0x00;
    result.MaxCount = 0x00;
    result.Counts = CountList(0x100, 0x00);

    for(uint64_t i = startoffset; i < endoffset; i++)
    {
        if(cancontinue && (!(*cancontinue)))
            break;

        uint8_t b = databuffer->at(i);
        uintmax_t& c = ++result.Counts.at(b);

        if(c > result.MaxCount)
        {
            result.MaxByte = b;
            result.MaxCount = c;
        }
    }
}

void ByteElaborator::scanStrings(ByteElaborator::StringList &result, IO::DataBuffer *databuffer, uint64_t startoffset, uint64_t endoffset, volatile bool *cancontinue)
{
    uint64_t len = 0;
    result.clear();

    for(uint64_t i = startoffset; i < endoffset; i++)
    {
        if(cancontinue && !(*cancontinue))
            break;

        uint8_t ch = databuffer->at(i);

        if(len == ByteElaborator::MAX_LENGTH)
        {
            result.push_back({i - len, i});
            len = 0;
            continue;
        }

        if(isprint(ch))
        {
            len++;
            continue;
        }

        if(len >= ByteElaborator::MIN_LENGTH)
        {
            result.push_back({i - len, i});
            len = 0;
            continue;
        }

        len = 0;
    }
}

} // namespace Support
} // namespace PrefLib

