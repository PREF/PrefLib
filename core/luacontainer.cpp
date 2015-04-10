#include "luacontainer.h"

namespace PrefLib {
namespace Core {

LuaContainer::LuaContainer()
{

}

LuaContainer::~LuaContainer()
{

}

void LuaContainer::append(bool val)
{
    lua_State* l = LuaState::instance();

    this->push();
    lua_pushboolean(l, val);
    lua_rawseti(l, -2, lua_rawlen(l, -2) + 1);
    lua_pop(l, 1);
}

void LuaContainer::append(const char *val)
{
    lua_State* l = LuaState::instance();

    this->push();
    lua_pushstring(l, val);
    lua_rawseti(l, -2, lua_rawlen(l, -2) + 1);
    lua_pop(l, 1);
}

void LuaContainer::append(lua_Integer val)
{
    lua_State* l = LuaState::instance();

    this->push();
    lua_pushinteger(l, val);
    lua_rawseti(l, -2, lua_rawlen(l, -2) + 1);
    lua_pop(l, 1);
}

void LuaContainer::append(lua_CFunction val)
{
    lua_State* l = LuaState::instance();

    this->push();
    lua_pushcfunction(l, val);
    lua_rawseti(l, -2, lua_rawlen(l, -2) + 1);
    lua_pop(l, 1);
}

void LuaContainer::append(LuaTable *val)
{
    lua_State* l = LuaState::instance();

    this->push();
    val->push();
    lua_rawseti(l, -2, lua_rawlen(l, -2) + 1);
    lua_pop(l, 1);
}

LuaContainer::Entry LuaContainer::operator[](lua_Integer idx)
{
    return Entry(*this, idx);
}

LuaContainer::Entry LuaContainer::operator[](const char *key)
{
    return Entry(*this, key);
}


} // namespace Core
} // namespace PrefLib

