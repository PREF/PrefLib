#include "luacontainer.h"

namespace PrefLib {
namespace Core {
namespace Lua {

LuaContainer::LuaContainer(lua_State *thread): LuaTable(thread)
{

}

LuaContainer::~LuaContainer()
{

}

void LuaContainer::pushMethod(const char *method)
{
    lua_getglobal(this->_thread, "table");
    lua_getfield(this->_thread, -1, method);
    lua_remove(this->_thread, -2);
}

void LuaContainer::append(bool val)
{
    this->pushMethod("insert");
    this->push();
    lua_pushboolean(this->_thread, val);
    lua_call(this->_thread, 3, 0);
}

void LuaContainer::append(const char *val)
{
    this->pushMethod("insert");
    this->push();
    lua_pushstring(this->_thread, val);
    lua_call(this->_thread, 3, 0);
}

void LuaContainer::append(lua_Integer val)
{
    this->pushMethod("insert");
    this->push();
    lua_pushinteger(this->_thread, val);
    lua_call(this->_thread, 3, 0);
}

void LuaContainer::append(lua_CFunction val)
{
    this->pushMethod("insert");
    this->push();
    lua_pushcfunction(this->_thread, val);
    lua_call(this->_thread, 3, 0);
}

void LuaContainer::append(LuaTable *val)
{
    this->pushMethod("insert");
    this->push();
    val->push();
    lua_call(this->_thread, 3, 0);
}

void LuaContainer::insert(lua_Integer idx, bool val)
{
    this->pushMethod("insert");
    this->push();
    lua_pushinteger(this->_thread, idx + 1);
    lua_pushboolean(this->_thread, val);
    lua_call(this->_thread, 3, 0);
}

void LuaContainer::insert(lua_Integer idx, const char *val)
{
    this->pushMethod("insert");
    this->push();
    lua_pushinteger(this->_thread, idx + 1);
    lua_pushstring(this->_thread, val);
    lua_call(this->_thread, 3, 0);
}

void LuaContainer::insert(lua_Integer idx, lua_Integer val)
{
    this->pushMethod("insert");
    this->push();
    lua_pushinteger(this->_thread, idx + 1);
    lua_pushinteger(this->_thread, val);
    lua_call(this->_thread, 3, 0);
}

void LuaContainer::insert(lua_Integer idx, lua_CFunction val)
{
    this->pushMethod("insert");
    this->push();
    lua_pushinteger(this->_thread, idx + 1);
    lua_pushcfunction(this->_thread, val);
    lua_call(this->_thread, 3, 0);
}

void LuaContainer::insert(lua_Integer idx, LuaTable *val)
{
    this->pushMethod("insert");
    this->push();
    lua_pushinteger(this->_thread, idx + 1);
    val->push();
    lua_call(this->_thread, 3, 0);
}

void LuaContainer::remove(lua_Integer idx)
{
    this->pushMethod("remove");
    this->push();
    lua_pushinteger(this->_thread, idx + 1);
    lua_call(this->_thread, 2, 0);
}

LuaContainer::Entry LuaContainer::operator[](lua_Integer idx)
{
    return Entry(*this, idx);
}

LuaContainer::Entry LuaContainer::operator[](const char *key)
{
    return Entry(*this, key);
}

} // namespace Lua
} // namespace Core
} // namespace PrefLib

