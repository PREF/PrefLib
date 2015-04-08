#ifndef PREFLIB_SUPPORT_BYTEELABORATOR_H
#define PREFLIB_SUPPORT_BYTEELABORATOR_H

#include <vector>
#include <cctype>
#include "../io/databuffer.h"

namespace PrefLib {
namespace Support {

using namespace Core;

class ByteElaborator
{
    public: // ByteElaborator::countBytes()
        typedef std::vector<uintmax_t> CountList;
        struct CountResult { uint8_t MaxByte; uintmax_t MaxCount; CountList Counts; };

    public: // ByteElaborator::scanStrings()
        struct StringRange { uint64_t Start; uint64_t End; };
        typedef std::vector<StringRange> StringList;

    private:
        ByteElaborator();
        ~ByteElaborator();

    public:
        static void countBytes(CountResult& result, IO::DataBuffer *databuffer, uint64_t startoffset, uint64_t endoffset, volatile bool* cancontinue = nullptr);
        static void scanStrings(StringList& result, IO::DataBuffer* databuffer, uint64_t startoffset, uint64_t endoffset, volatile bool* cancontinue = nullptr);

    private:
        static const uint64_t MIN_LENGTH;
        static const uint64_t MAX_LENGTH;
};

} // namespace Support
} // namespace PrefLib

#endif // PREFLIB_SUPPORT_BYTEELABORATOR_H
