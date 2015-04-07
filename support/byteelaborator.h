#ifndef PREFLIB_SUPPORT_BYTEELABORATOR_H
#define PREFLIB_SUPPORT_BYTEELABORATOR_H

#include <vector>
#include "../io/databuffer.h"

namespace PrefLib {
namespace Support {

using namespace Core;

class ByteElaborator
{
    public:
        typedef std::vector<uintmax_t> CountList;

        struct CountResult
        {
            uint8_t MaxByte;
            uintmax_t MaxCount;
            CountList Counts;
        };

    private:
        ByteElaborator();
        ~ByteElaborator();

    public:
        static void countBytes(CountResult& result, IO::DataBuffer *databuffer, uint64_t startoffset, uint64_t endoffset, volatile bool* cancontinue = nullptr);
};

} // namespace Support
} // namespace PrefLib

#endif // PREFLIB_SUPPORT_BYTEELABORATOR_H
