#include "prefcontext.h"

namespace PrefLib {

PrefContext* PrefContext::_instance = nullptr;
luaL_Reg PrefContext::_functions[] = { { "log", &PrefContext::luaLog },
                                       { "logline", &PrefContext::luaLogLine },
                                       { "notice", &PrefContext::luaNotice },
                                       { "warning", &PrefContext::luaWarning },
                                       { "error", &PrefContext::luaError },
                                       { nullptr, nullptr } };

PrefContext::PrefContext(): _logger(&PrefContext::defaultLogger), _loguserdata(nullptr)
{
    luaL_openlibs(LuaState::instance());
    luaopen_capstone(LuaState::instance());

    this->_exporterctx = new Exporter::ExporterContext();
    this->_formatctx = new Format::FormatContext();
    this->_disassemblerctx = new Disassembler::DisassemblerContext();
}

void PrefContext::logger(PrefContext::LogLevel level, lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectminargc(l, argc, 1);

    lua_getglobal(l, "string");
    lua_getfield(l, -1, "format");

    for(int i = 1; i <= argc; i++)
        lua_pushvalue(l, i);

    lua_call(l, argc, 1);
    PrefContext::_instance->_logger(level, lua_tostring(l, -1), PrefContext::_instance->_loguserdata);
    lua_pop(l, 2);
}

void PrefContext::defaultLogger(PrefContext::LogLevel level, const char *msg, void*)
{
    switch(level)
    {
        case LogLevel::Notice:
            std::cout << "NOTICE: " << msg << std::endl;
            break;

        case LogLevel::Warning:
            std::cout << "WARNING: " << msg << std::endl;
            break;

        case LogLevel::Error:
            std::cout << "ERROR: " << msg << std::endl;
            break;

        default:
            std::cout << msg << std::endl;
            break;
    }
}

int PrefContext::luaopen_preflib(lua_State* l)
{
    PrefContext* instance = PrefContext::instance();
    luaL_newlib(l, PrefContext::_functions);

    Endianness::pushTable(l);
    lua_setfield(l, -2, "endianness");

    DataType::pushTable(l);
    lua_setfield(l, -2, "datatype");

    Support::Math::pushTable(l);
    lua_setfield(l, -2, "math");

    instance->_exporterctx->push();
    lua_setfield(l, -2, "exporter");

    instance->_formatctx->push();
    lua_setfield(l, -2, "format");

    instance->_disassemblerctx->push();
    lua_setfield(l, -2, "disassembler");

    return 1;
}

int PrefContext::luaLog(lua_State *l)
{
    PrefContext::logger(LogLevel::Normal, l);
    return 0;
}

int PrefContext::luaLogLine(lua_State *l)
{
    PrefContext::logger(LogLevel::NormalLine, l);
    return 0;
}

int PrefContext::luaNotice(lua_State *l)
{
    PrefContext::logger(LogLevel::Notice, l);
    return 0;
}

int PrefContext::luaWarning(lua_State *l)
{
    PrefContext::logger(LogLevel::Warning, l);
    return 0;
}

int PrefContext::luaError(lua_State *l)
{
    PrefContext::logger(LogLevel::Error, l);
    return 0;
}

PrefContext::~PrefContext()
{
    if(this->_formatctx)
    {
        delete this->_formatctx;
        this->_formatctx = nullptr;
    }

    if(this->_exporterctx)
    {
        delete this->_exporterctx;
        this->_exporterctx = nullptr;
    }

    LuaState::instance().close();
}

const LuaState &PrefContext::state() const
{
    return LuaState::instance();
}

Format::FormatContext *PrefContext::formats() const
{
    return this->_formatctx;
}

Disassembler::DisassemblerContext *PrefContext::disassemblers() const
{
    return this->_disassemblerctx;
}

Exporter::ExporterContext *PrefContext::exporters() const
{
    return this->_exporterctx;
}

void PrefContext::addSearchPath(const char *path)
{
    lua_State* l = LuaState::instance();
    lua_getglobal(l, "package");
    lua_getfield(l, -1, "path");

    const char* origpath = lua_tostring(l, -1);
    lua_pop(l, 1); /* Pop "path" */

    size_t len = strlen(origpath) + 1 + strlen(path); /* Take care of Separator */
    char* newpath = new char[len + 1];
    newpath[len] = '\0';

    std::snprintf(newpath, len, "%s;%s/?.lua", origpath, path);
    lua_pushstring(l, newpath);
    lua_setfield(l, -2, "path");
    delete[] newpath;
}

void PrefContext::executeScript(const char *script)
{
    lua_State* l = LuaState::instance();
    int res = luaL_dofile(l, script);

    if(res)
    {
        throw std::runtime_error(lua_tostring(l, -1));
        lua_pop(l, 1);
    }
}

void PrefContext::setLogger(PrefContext::LogCallback logger, void *userdata)
{
    this->_logger = logger;
    this->_loguserdata = userdata;
}

PrefContext *PrefContext::instance()
{
    if(!PrefContext::_instance)
    {
        PrefContext::_instance = new PrefContext();
        luaL_requiref(LuaState::instance(), "pref", &PrefContext::luaopen_preflib, false);
    }

    return PrefContext::_instance;
}

} // namespace PrefLib

