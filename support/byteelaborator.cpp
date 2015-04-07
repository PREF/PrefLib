#include "byteelaborator.h"

namespace PrefLib {
namespace Support {

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

} // namespace Support
} // namespace PrefLib

