#ifndef PREFLIB_DISASSEMBLER_DISASSEMBLERLISTING_H
#define PREFLIB_DISASSEMBLER_DISASSEMBLERLISTING_H

#include "../core/luax.h"
#include "../core/luatable.h"
#include "../core/luacontainer.h"
#include "blocks/segment.h"

namespace PrefLib {
namespace Disassembler {

using namespace Core;

class DisassemblerListing: public LuaTable
{
    public:
        DisassemblerListing();
        ~DisassemblerListing();

    public:
        LuaContainer& segments();
        void createSegment(const char* name, Segment::Type segmenttype, uint64_t startaddress, uint64_t size, uint64_t offset);

    lua_api:
        static int luaCreateSegment(lua_State* l);

    private:
        LuaContainer _segments;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_DISASSEMBLERLISTING_H
