#include "exportercontext.h"

namespace PrefLib {
namespace Exporter {

ExporterContext::ExporterContext(lua_State *thread): LuaTable(thread)
{
    this->setFunction("create", &ExporterContext::luaCreate);
}

ExporterContext::~ExporterContext()
{

}

ExporterDefinition *ExporterContext::get(int idx) const
{
    ExporterDefinition* exporterdefinition = nullptr;

    this->push();
    lua_rawgeti(this->_thread, -1, idx + 1);

    if(!lua_isnoneornil(this->_thread, -1))
        exporterdefinition = reinterpret_cast<ExporterDefinition*>(checkThis(this->_thread, -1));

    lua_pop(this->_thread, 2);
    return exporterdefinition;
}

int ExporterContext::luaCreate(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 5);

    ExporterContext* thethis = reinterpret_cast<ExporterContext*>(checkThis(l, 1));
    ExporterDefinition* ed = new ExporterDefinition(luaL_checkstring(l, 2), luaL_checkstring(l, 3), luaL_checkstring(l, 4), luaL_checkstring(l, 5));

    ed->push();
    lua_seti(l, 1, thethis->length() + 1);
    ed->push();
    return 1;
}

} // namespace Exporter
} // namespace PrefLib

