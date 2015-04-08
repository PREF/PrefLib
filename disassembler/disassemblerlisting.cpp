#include "disassemblerlisting.h"

namespace PrefLib {
namespace Disassembler {

DisassemblerListing::DisassemblerListing(): LuaTable()
{
    lua_State* l = LuaState::instance();

    this->push();
    this->setFunction("createsegment", &DisassemblerListing::luaCreateSegment);
    lua_pop(l, 1);
}

DisassemblerListing::~DisassemblerListing()
{

}

void DisassemblerListing::createSegment(const char *name, int segmenttype, uint64_t startaddress, uint64_t size_t, uint64_t offset)
{

}

int DisassemblerListing::luaCreateSegment(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 6);

    DisassemblerListing* thethis = reinterpret_cast<DisassemblerListing*>(checkThis(l, 1));
    thethis->createSegment(luaL_checkstring(l, 2), luaL_checkinteger(l, 3), luaL_checkinteger(l, 4), luaL_checkinteger(l, 5), luaL_checkinteger(l, 6));
    return 0;
}

} // namespace Disassembler
} // namespace PrefLib

