#ifndef PREFLIB_DISASSEMBLER_DISASSEMBLERLISTING_H
#define PREFLIB_DISASSEMBLER_DISASSEMBLERLISTING_H

#include "../core/luax.h"
#include "../core/luatable.h"

namespace PrefLib {
namespace Disassembler {

using namespace Core;

class DisassemblerListing: public LuaTable
{
    public:
        DisassemblerListing();
        ~DisassemblerListing();

    public:
        void createSegment(const char* name, int segmenttype, uint64_t startaddress, uint64_t size_t, uint64_t offset);

    lua_api:
        static int luaCreateSegment(lua_State* l);
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_DISASSEMBLERLISTING_H
