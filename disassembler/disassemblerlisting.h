#ifndef PREFLIB_DISASSEMBLER_DISASSEMBLERLISTING_H
#define PREFLIB_DISASSEMBLER_DISASSEMBLERLISTING_H

#include "../core/luax.h"
#include "../core/luatable.h"
#include "../core/luacontainer.h"
#include "blocks/segment.h"
#include "blocks/function.h"

namespace PrefLib {
namespace Disassembler {

using namespace Core;

class DisassemblerListing: public LuaTable
{
    private:
        struct BlockContainer { LuaContainer ByIndex; LuaContainer ByAddress; };

    public:
        DisassemblerListing();
        ~DisassemblerListing();

    public:
        LuaContainer& segments();
        LuaContainer& functions();
        LuaContainer& entryPoints();
        void createSegment(const char* name, Segment::Type segmenttype, uint64_t startaddress, uint64_t size, uint64_t offset);
        void createFunction(const char* name, Function::Type functiontype, uint64_t address);
        void createEntryPoint(const char* name, uint64_t address);

    lua_api:
        static int luaCreateSegment(lua_State* l);
        static int luaCreateFunction(lua_State* l);
        static int luaCreateEntryPoint(lua_State* l);

    private:
        BlockContainer _segments;
        BlockContainer _functions;
        BlockContainer _entrypoints;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_DISASSEMBLERLISTING_H
