#include "disassemblerlisting.h"

namespace PrefLib {
namespace Disassembler {

DisassemblerListing::DisassemblerListing(): LuaTable()
{
    lua_State* l = LuaState::instance();

    this->push();
    this->setTable("segments", &this->_segments);
    this->setFunction("createsegment", &DisassemblerListing::luaCreateSegment);
    lua_pop(l, 1);
}

DisassemblerListing::~DisassemblerListing()
{

}

LuaContainer& DisassemblerListing::segments()
{
    return this->_segments;
}

void DisassemblerListing::createSegment(const char *name, Segment::Type segmenttype, uint64_t startaddress, uint64_t size, uint64_t baseoffset)
{
    Segment* segment = new Segment(name, segmenttype, startaddress, size, baseoffset);
    this->_segments.append(segment);
}

int DisassemblerListing::luaCreateSegment(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 6);

    DisassemblerListing* thethis = reinterpret_cast<DisassemblerListing*>(checkThis(l, 1));
    thethis->createSegment(luaL_checkstring(l, 2), static_cast<Segment::Type>(luaL_checkinteger(l, 3)), luaL_checkinteger(l, 4), luaL_checkinteger(l, 5), luaL_checkinteger(l, 6));
    return 0;
}

} // namespace Disassembler
} // namespace PrefLib

