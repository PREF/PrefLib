#include "disassemblercontext.h"

namespace PrefLib {
namespace Disassembler {

DisassemblerContext::DisassemblerContext(lua_State* thread): LuaTable(thread)
{
    this->setFunction("create", &DisassemblerContext::luaCreate);
}

DisassemblerContext::~DisassemblerContext()
{

}

void DisassemblerContext::push() const
{
    LuaTable::push();

    lua_newtable(this->_thread);
    lua_pushinteger(this->_thread, Segment::Code);
    lua_setfield(this->_thread, -2, "Code");
    lua_pushinteger(this->_thread, Segment::Data);
    lua_setfield(this->_thread, -2, "Data");
    lua_setfield(this->_thread, -2, "segmenttype");

    lua_newtable(this->_thread);
    lua_pushinteger(this->_thread, Function::FunctionBlock);
    lua_setfield(this->_thread, -2, "Function");
    lua_pushinteger(this->_thread, Function::EntryPointBlock);
    lua_setfield(this->_thread, -2, "EntryPoint");
    lua_pushinteger(this->_thread, Function::ExportBlock);
    lua_setfield(this->_thread, -2, "Export");
    lua_pushinteger(this->_thread, Function::ImportBlock);
    lua_setfield(this->_thread, -2, "Import");
    lua_setfield(this->_thread, -2, "functiontype");
}

DisassemblerDefinition *DisassemblerContext::get(int idx) const
{
    DisassemblerDefinition* disassemblerdefinition = nullptr;

    this->push();
    lua_rawgeti(this->_thread, -1, idx + 1);

    if(!lua_isnoneornil(this->_thread, -1))
        disassemblerdefinition = reinterpret_cast<DisassemblerDefinition*>(checkThis(this->_thread, -1));

    lua_pop(this->_thread, 2);
    return disassemblerdefinition;
}

int DisassemblerContext::luaCreate(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 6);

    DisassemblerContext* thethis = reinterpret_cast<DisassemblerContext*>(checkThis(l, 1));

    DisassemblerDefinition* dd = new DisassemblerDefinition(luaL_checkstring(l, 2), reinterpret_cast<Format::FormatDefinition*>(checkThis(l, 3)),
                                                            static_cast<DataType::Type>(luaL_checkinteger(l, 4)), luaL_checkstring(l, 5), luaL_checkstring(l, 6));

    thethis->bindTable(dd->name(), dd);
    dd->push();
    return 1;
}

} // namespace Disassembler
} // namespace PrefLib

