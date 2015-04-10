#include "prefcontext.h"

namespace PrefLib {

PrefContext* PrefContext::_instance = nullptr;
luaL_Reg PrefContext::_functions[] = { { nullptr, nullptr } };

PrefContext::PrefContext()
{
    luaL_openlibs(Core::LuaState::instance());
    luaopen_capstone(Core::LuaState::instance());

    this->_exporterctx = new Exporter::ExporterContext();
    this->_formatctx = new Format::FormatContext();
    this->_disassemblerctx = new Disassembler::DisassemblerContext();
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

    Core::LuaState::instance().close();
}

const Core::LuaState &PrefContext::state() const
{
    return Core::LuaState::instance();
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
    lua_State* l = Core::LuaState::instance();
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
    lua_State* l = Core::LuaState::instance();
    int res = luaL_dofile(l, script);

    if(res)
    {
        throw std::runtime_error(lua_tostring(l, -1));
        lua_pop(l, 1);
    }
}

PrefContext *PrefContext::instance()
{
    if(!PrefContext::_instance)
    {
        PrefContext::_instance = new PrefContext();
        luaL_requiref(Core::LuaState::instance(), "pref", &PrefContext::luaopen_preflib, false);
    }

    return PrefContext::_instance;
}

} // namespace PrefLib

