#include "disassemblerlisting.h"

namespace PrefLib {
namespace Disassembler {

DisassemblerListing::DisassemblerListing(): LuaTable()
{
    lua_State* l = LuaState::instance();

    this->push();
    this->setTable("segments", &this->_segments.ByIndex);
    this->setTable("segmentmap", &this->_segments.ByAddress);
    this->setTable("functions", &this->_functions.ByIndex);
    this->setTable("functionmap", &this->_functions.ByAddress);
    this->setTable("entrypoints", &this->_entrypoints.ByIndex);
    this->setTable("entrypointmap", &this->_entrypoints.ByAddress);
    this->setFunction("createsegment", &DisassemblerListing::luaCreateSegment);
    this->setFunction("createfunction", &DisassemblerListing::luaCreateFunction);
    this->setFunction("createentrypoint", &DisassemblerListing::luaCreateEntryPoint);
    lua_pop(l, 1);
}

DisassemblerListing::~DisassemblerListing()
{

}

LuaContainer& DisassemblerListing::segments()
{
    return this->_segments.ByIndex;
}

LuaContainer &DisassemblerListing::functions()
{
    return this->_functions.ByIndex;
}

LuaContainer &DisassemblerListing::entryPoints()
{
   return this->_entrypoints.ByIndex;
}

void DisassemblerListing::createSegment(const char *name, Segment::Type segmenttype, uint64_t startaddress, uint64_t size, uint64_t baseoffset)
{
    Segment* segment = new Segment(name, segmenttype, startaddress, size, baseoffset);

    this->_segments.ByIndex.append(segment);
    this->_segments.ByAddress[startaddress] = segment;
}

void DisassemblerListing::createFunction(const char *name, Function::Type functiontype, uint64_t address)
{
    Function* function = new Function(name, functiontype, address);

    this->_functions.ByIndex.append(function);
    this->_functions.ByAddress[name] = function;

    if(functiontype & Function::EntryPointBlock)
    {
        this->_entrypoints.ByIndex.append(function);
        this->_entrypoints.ByAddress[name] = function;
    }
}

void DisassemblerListing::createEntryPoint(const char *name, uint64_t address)
{
    this->createFunction(name, Function::EntryPointBlock, address);
}

int DisassemblerListing::luaCreateSegment(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 6);

    DisassemblerListing* thethis = reinterpret_cast<DisassemblerListing*>(checkThis(l, 1));
    thethis->createSegment(luaL_checkstring(l, 2), static_cast<Segment::Type>(luaL_checkinteger(l, 3)), luaL_checkinteger(l, 4), luaL_checkinteger(l, 5), luaL_checkinteger(l, 6));
    return 0;
}

int DisassemblerListing::luaCreateFunction(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 4);

    DisassemblerListing* thethis = reinterpret_cast<DisassemblerListing*>(checkThis(l, 1));
    thethis->createFunction(luaL_checkstring(l, 2), static_cast<Function::Type>(luaL_checkinteger(l, 3)), luaL_checkinteger(l, 3));
    return 0;
}

int DisassemblerListing::luaCreateEntryPoint(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 3);

    DisassemblerListing* thethis = reinterpret_cast<DisassemblerListing*>(checkThis(l, 1));
    thethis->createEntryPoint(luaL_checkstring(l, 2), luaL_checkinteger(l, 2));
    return 0;
}

} // namespace Disassembler
} // namespace PrefLib

