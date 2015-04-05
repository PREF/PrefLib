#include "prefcontext.h"

namespace PrefLib {

PrefContext* PrefContext::_instance = nullptr;
luaL_Reg PrefContext::_functions[] = { { nullptr, nullptr } };

PrefContext::PrefContext()
{
    luaL_openlibs(Core::LuaState::instance());
    this->_formatctx = new Format::FormatContext();
}

int PrefContext::luaopen_preflib(lua_State* l)
{
    PrefContext* instance = PrefContext::instance();
    luaL_newlib(l, PrefContext::_functions);

    instance->_formatctx->push();
    lua_setfield(l, -2, "format");

    luaregister_datatype(l);
    lua_setfield(l, -2, "datatype");
    return 1;
}

void PrefContext::luaregister_datatype(lua_State *l)
{
    lua_newtable(l);

    lua_pushinteger(l, DataType::Invalid);
    lua_setfield(l, -2, "Invalid");

    lua_pushinteger(l, DataType::UInt8);
    lua_setfield(l, -2, "UInt8");
    lua_pushinteger(l, DataType::UInt16);
    lua_setfield(l, -2, "UInt16");
    lua_pushinteger(l, DataType::UInt32);
    lua_setfield(l, -2, "UInt32");
    lua_pushinteger(l, DataType::UInt64);
    lua_setfield(l, -2, "UInt64");

    lua_pushinteger(l, DataType::Int8);
    lua_setfield(l, -2, "Int8");
    lua_pushinteger(l, DataType::Int16);
    lua_setfield(l, -2, "Int16");
    lua_pushinteger(l, DataType::Int32);
    lua_setfield(l, -2, "Int32");
    lua_pushinteger(l, DataType::Int64);
    lua_setfield(l, -2, "Int64");

    lua_pushinteger(l, DataType::UInt16_LE);
    lua_setfield(l, -2, "UInt16_LE");
    lua_pushinteger(l, DataType::UInt32_LE);
    lua_setfield(l, -2, "UInt32_LE");
    lua_pushinteger(l, DataType::UInt64_LE);
    lua_setfield(l, -2, "UInt64_LE");

    lua_pushinteger(l, DataType::Int16_LE);
    lua_setfield(l, -2, "Int16_LE");
    lua_pushinteger(l, DataType::Int32_LE);
    lua_setfield(l, -2, "Int32_LE");
    lua_pushinteger(l, DataType::Int64_LE);
    lua_setfield(l, -2, "Int64_LE");

    lua_pushinteger(l, DataType::UInt16_BE);
    lua_setfield(l, -2, "UInt16_BE");
    lua_pushinteger(l, DataType::UInt32_BE);
    lua_setfield(l, -2, "UInt32_BE");
    lua_pushinteger(l, DataType::UInt64_BE);
    lua_setfield(l, -2, "UInt64_BE");

    lua_pushinteger(l, DataType::Int16_BE);
    lua_setfield(l, -2, "Int16_BE");
    lua_pushinteger(l, DataType::Int32_BE);
    lua_setfield(l, -2, "Int32_BE");
    lua_pushinteger(l, DataType::Int64_BE);
    lua_setfield(l, -2, "Int64_BE");

    lua_pushinteger(l, DataType::AsciiCharacter);
    lua_setfield(l, -2, "AsciiCharacter");
    lua_pushinteger(l, DataType::UnicodeCharacter);
    lua_setfield(l, -2, "UnicodeCharacter");
    lua_pushinteger(l, DataType::Character);
    lua_setfield(l, -2, "Character");

    lua_pushinteger(l, DataType::Array);
    lua_setfield(l, -2, "Array");
    lua_pushinteger(l, DataType::AsciiString);
    lua_setfield(l, -2, "AsciiString");
    lua_pushinteger(l, DataType::UnicodeString);
    lua_setfield(l, -2, "UnicodeString");

    lua_pushinteger(l, DataType::Blob);
    lua_setfield(l, -2, "Blob");
}

PrefContext::~PrefContext()
{
    if(PrefContext::_formatctx)
    {
        delete PrefContext::_formatctx;
        PrefContext::_formatctx = nullptr;
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
        throw PrefException(lua_tostring(l, -1));
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

