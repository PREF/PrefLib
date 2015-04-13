#include "formatcontext.h"

namespace PrefLib {
namespace Format {

FormatContext::FormatContext(): LuaTable()
{
    this->setFunction("create", &FormatContext::luaCreate);
}

FormatContext::~FormatContext()
{

}

FormatDefinition *FormatContext::get(int idx) const
{
    lua_State* l = LuaState::instance();
    FormatDefinition* formatdefinition = nullptr;

    this->push();
    lua_rawgeti(l, -1, idx + 1);

    if(!lua_isnoneornil(l, -1))
        formatdefinition = reinterpret_cast<FormatDefinition*>(checkThis(l, -1));

    lua_pop(l, 2);
    return formatdefinition;
}

int FormatContext::luaCreate(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 5);

    FormatContext* thethis = reinterpret_cast<FormatContext*>(checkThis(l, 1));
    FormatDefinition* fd = new FormatDefinition(luaL_checkstring(l, 2), luaL_checkstring(l, 3), luaL_checkstring(l, 4), luaL_checkstring(l, 5));

    thethis->bindTable(fd->name(), fd);
    fd->push();
    return 1;
}

} // namespace Format
} // namespace PrefLib
