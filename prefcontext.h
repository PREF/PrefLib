#ifndef PREFLIB_PREFCONTEXT_H
#define PREFLIB_PREFCONTEXT_H

#include <iostream>
#include "core/capstone/luacapstone.h"
#include "core/lua/luastate.h"
#include "support/math.h"
#include "support/algorithm.h"
#include "exporter/exportercontext.h"
#include "format/formatcontext.h"
#include "disassembler/disassemblercontext.h"

namespace PrefLib {

using namespace Core::Lua;
using namespace Core::Capstone;

class PrefContext
{
    public:
        enum LogLevel { Normal, NormalLine, Notice, Warning, Error };
        typedef void (*LogCallback)(LogLevel level, const char* msg, void* userdata);

    private:
        PrefContext();
        static void logger(LogLevel level, lua_State* l);
        static void defaultLogger(LogLevel level, const char* msg, void*);

    lua_api:
        static int luaopen_preflib(lua_State *l);
        static int luaLog(lua_State* l);
        static int luaLogLine(lua_State* l);
        static int luaNotice(lua_State* l);
        static int luaWarning(lua_State* l);
        static int luaError(lua_State* l);

    public:
        ~PrefContext();
        const LuaState& state() const;
        Exporter::ExporterContext* exporters() const;
        Format::FormatContext* formats() const;
        Disassembler::DisassemblerContext* disassemblers() const;
        void addSearchPath(const char* path);
        void executeScript(const char* script);
        void setLogger(LogCallback logger, void* userdata = nullptr);

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
        LogCallback _logger;
        void* _loguserdata;
};

} // namespace PrefLib

#endif // PREFLIB_PREFCONTEXT_H
