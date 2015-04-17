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

void LuaContainer::append(bool val)
{
    this->push();
    lua_pushboolean(this->_thread, val);
    lua_rawseti(this->_thread, -2, lua_rawlen(this->_thread, -2) + 1);
    lua_pop(this->_thread, 1);
}

void LuaContainer::append(const char *val)
{
    this->push();
    lua_pushstring(this->_thread, val);
    lua_rawseti(this->_thread, -2, lua_rawlen(this->_thread, -2) + 1);
    lua_pop(this->_thread, 1);
}

void LuaContainer::append(lua_Integer val)
{
    this->push();
    lua_pushinteger(this->_thread, val);
    lua_rawseti(this->_thread, -2, lua_rawlen(this->_thread, -2) + 1);
    lua_pop(this->_thread, 1);
}

void LuaContainer::append(lua_CFunction val)
{
    this->push();
    lua_pushcfunction(this->_thread, val);
    lua_rawseti(this->_thread, -2, lua_rawlen(this->_thread, -2) + 1);
    lua_pop(this->_thread, 1);
}

void LuaContainer::append(LuaTable *val)
{
    this->push();
    val->push();
    lua_rawseti(this->_thread, -2, lua_rawlen(this->_thread, -2) + 1);
    lua_pop(this->_thread, 1);
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

