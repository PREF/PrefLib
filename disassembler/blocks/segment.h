#ifndef PREFLIB_DISASSEMBLER_SEGMENT_H
#define PREFLIB_DISASSEMBLER_SEGMENT_H

#include "block.h"

namespace PrefLib {
namespace Disassembler {

class Segment: public Block
{
    public:
        enum Type { Code, Data };

    public:
        Segment(const char* name, Segment::Type segmenttype, uint64_t startaddress, uint64_t size, uint64_t baseoffset);
        ~Segment();

    public:
        bool isCode() const;
        bool isData() const;
        const char* name() const;

    protected:
        virtual Block::Type type() const;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_SEGMENT_H