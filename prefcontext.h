#ifndef PREFLIB_PREFCONTEXT_H
#define PREFLIB_PREFCONTEXT_H

#include <lua.hpp>
#include <cstdio>
#include <cstring>
#include "core/luastate.h"
#include "support/math.h"
#include "format/formatcontext.h"
#include "exporter/exportercontext.h"

namespace PrefLib {

class PrefContext
{
    private:
        PrefContext();

    private:
        static int luaopen_preflib(lua_State *l);
        static void luaregister_datatype(lua_State* l);

    public:
        ~PrefContext();
        const Core::LuaState& state() const;
        Format::FormatContext* formats() const;
        Exporter::ExporterContext* exporters() const;
        void addSearchPath(const char* path);
        void executeScript(const char* script);

    public:
        static PrefContext* instance();

    private:
        static PrefContext* _instance;
        static luaL_Reg _functions[];

    private:
        lua_State* _state;
        Format::FormatContext* _formatctx;
        Exporter::ExporterContext* _exporterctx;
};

} // namespace PrefLib

#endif // PREFLIB_PREFCONTEXT_H
