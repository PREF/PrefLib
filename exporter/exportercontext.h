#ifndef PREFLIB_EXPORTER_EXPORTERCONTEXT_H
#define PREFLIB_EXPORTER_EXPORTERCONTEXT_H

#include "../core/lua/luax.h"
#include "../core/lua/luatable.h"
#include "exporterdefinition.h"

namespace PrefLib {
namespace Exporter {

using namespace Core::Lua;

class ExporterContext : public LuaTable
{
    public:
        ExporterContext();
        ~ExporterContext();

    public:
        ExporterDefinition* get(int idx) const;

    lua_api:
        static int luaCreate(lua_State *l);
};

} // namespace Exporter
} // namespace PrefLib

#endif // PREFLIB_EXPORTER_EXPORTERCONTEXT_H
