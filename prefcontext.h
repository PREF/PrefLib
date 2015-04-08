#ifndef PREFLIB_PREFCONTEXT_H
#define PREFLIB_PREFCONTEXT_H

#include <lua.hpp>
#include <cstdio>
#include <cstring>
#include "core/luastate.h"
#include "support/math.h"
#include "exporter/exportercontext.h"
#include "format/formatcontext.h"
#include "disassembler/disassemblercontext.h"

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
        Exporter::ExporterContext* exporters() const;
        Format::FormatContext* formats() const;
        Disassembler::DisassemblerContext* disassemblers() const;
        void addSearchPath(const char* path);
        void executeScript(const char* script);

    public:
        static PrefContext* instance();

    private:
        static PrefContext* _instance;
        static luaL_Reg _functions[];

    private:
        lua_State* _state;
        Exporter::ExporterContext* _exporterctx;
        Format::FormatContext* _formatctx;
        Disassembler::DisassemblerContext* _disassemblerctx;
};

} // namespace PrefLib

#endif // PREFLIB_PREFCONTEXT_H
