#include "luatable.h"

namespace PrefLib {
namespace Core {
namespace Lua {

LuaTable::LuaTable(lua_State *thread): LuaReference(thread)
{
    lua_newtable(this->_thread);

    lua_pushstring(this->_thread, SELF_FIELD);
    lua_pushlightuserdata(this->_thread, this);
    lua_rawset(this->_thread, -3);

    this->_reference = luaL_ref(this->_thread, LUA_REGISTRYINDEX);
}

LuaTable::LuaTable(int idx): LuaReference()
{
    lua_pushvalue(this->_thread, idx);

    lua_pushstring(this->_thread, SELF_FIELD);
    lua_pushlightuserdata(this->_thread, this);
    lua_rawset(this->_thread, -3);
    this->_reference = luaL_ref(this->_thread, LUA_REGISTRYINDEX);
}

LuaTable::~LuaTable()
{

}

LuaTable *LuaTable::bindedTable(int i) const
{
    LuaTable* t = nullptr;

    this->push();
    lua_rawgeti(this->_thread, -1, i + 1);

    if(!lua_isnoneornil(this->_thread, -1))
        t = reinterpret_cast<LuaTable*>(checkThis(this->_thread, -1));

    lua_pop(this->_thread, 2);
    return t;
}

LuaTable *LuaTable::bindedTable(const char *name) const
{
    LuaTable* t = nullptr;

    this->push();
    lua_pushstring(this->_thread, name);
    lua_rawget(this->_thread, -2);

    if(!lua_isnoneornil(this->_thread, -1))
        t = reinterpret_cast<LuaTable*>(checkThis(this->_thread, -1));

    lua_pop(this->_thread, 2);
    return t;
}

LuaTable *LuaTable::firstBindedTable() const
{
    return this->bindedTable(0);
}

LuaTable *LuaTable::lastBindedTable()
{
    return this->bindedTable(this->length() - 1);
}

void LuaTable::bindTable(const char *name, LuaTable *t)
{
    this->push();
    this->setTable(name, t); // Allow self.foo
    this->setI(this->length() + 1, t); // Allow self[i]
    lua_pop(this->_thread, 1);
}

void *LuaTable::checkThis(lua_State *l, int idx)
{
    int t = lua_type(l, idx);

    if(t != LUA_TTABLE)
    {
        luaL_error(l, "LuaTable::checkThis(): Bad argument #%d (table expected, got %s)", idx, lua_typename(l, t));
        return nullptr;
    }

    lua_pushstring(l, SELF_FIELD);
    lua_rawget(l, (idx > 0 ? idx : idx - 1));

    if(!lua_islightuserdata(l, -1) && !lua_isuserdata(l, -1))
    {
        lua_pop(l, 1);
        luaL_error(l, "LuaTable::checkThis(): Invalid 'self' argument, type %s given", idx, lua_typename(l, t));
        return nullptr;
    }

    void* thethis = lua_touserdata(l, -1);
    lua_pop(l, 1);
    return thethis;
}

size_t LuaTable::length() const
{
    this->push();
    size_t len = lua_rawlen(this->_thread, -1);

    lua_pop(this->_thread, 1);
    return len;
}

void LuaTable::protectedCall(int nargs, int nres) const
{
    int res = lua_pcall(this->_thread, nargs, nres, 0);

    if(res)
    {
        throw std::runtime_error(lua_tostring(this->_thread, -1));
        lua_pop(this->_thread, 1);
    }
}

bool LuaTable::hasField(const char *k) const
{
    bool res = false;

    this->push();
    lua_pushstring(this->_thread, k);
    lua_rawget(this->_thread, -2);

    res = !lua_isnoneornil(this->_thread, -1);
    lua_pop(this->_thread, 2);
    return res;
}

bool LuaTable::hasField(lua_Integer i) const
{
    bool res = false;

    this->push();
    lua_pushinteger(this->_thread, i);
    lua_rawget(this->_thread, -2);

    res = !lua_isnoneornil(this->_thread, -1);
    lua_pop(this->_thread, 2);
    return res;
}

const char *LuaTable::getString(const char *k) const
{
    this->push();
    lua_pushstring(this->_thread, k);
    lua_rawget(this->_thread, -2);

    const char* res = luaL_checkstring(this->_thread, -1);
    lua_pop(this->_thread, 2);
    return res;
}

lua_Integer LuaTable::getInteger(const char *k) const
{
    this->push();
    lua_pushstring(this->_thread, k);
    lua_rawget(this->_thread, -2);

    lua_Integer res = luaL_checkinteger(this->_thread, -1);
    lua_pop(this->_thread, 2);
    return res;
}

bool LuaTable::getBoolean(const char *k) const
{
    this->push();
    lua_pushstring(this->_thread, k);
    lua_rawget(this->_thread, -2);

    bool res = lua_toboolean(this->_thread, -1) != 0;
    lua_pop(this->_thread, 2);
    return res;
}

LuaTable *LuaTable::getTable(const char *k) const
{
    this->push();
    lua_pushstring(this->_thread, k);
    lua_rawget(this->_thread, -2);

    LuaTable* res = reinterpret_cast<LuaTable*>(checkThis(this->_thread, -1));
    lua_pop(this->_thread, 2);
    return res;
}

lua_CFunction LuaTable::getFunction(const char *k) const
{
    this->push();
    lua_pushstring(this->_thread, k);
    lua_rawget(this->_thread, -2);

    lua_CFunction res = lua_tocfunction(this->_thread, -1);
    lua_pop(this->_thread, 2);
    return res;
}

template<> bool LuaTable::getI<bool>(int i) const
{
    this->push();
    lua_rawgeti(this->_thread, -1, i + 1);

    bool res = lua_toboolean(this->_thread, -1) == true;
    lua_pop(this->_thread, 2);
    return res;
}

template<> const char* LuaTable::getI<const char*>(int i) const
{
    this->push();
    lua_rawgeti(this->_thread, -1, i + 1);

    const char* res = luaL_checkstring(this->_thread, -1);
    lua_pop(this->_thread, 2);
    return res;
}

template<> lua_Integer LuaTable::getI<lua_Integer>(int i) const
{
    this->push();
    lua_rawgeti(this->_thread, -1, i + 1);

    lua_Integer res = luaL_checkinteger(this->_thread, -1);
    lua_pop(this->_thread, 2);
    return res;
}

template<> LuaTable* LuaTable::getI<LuaTable*>(int i) const
{
    this->push();
    lua_rawgeti(this->_thread, -1, i + 1);

    LuaTable* res = reinterpret_cast<LuaTable*>(checkThis(this->_thread, -1));
    lua_pop(this->_thread, 2);
    return res;
}

template<> lua_CFunction LuaTable::getI<lua_CFunction>(int i) const
{
    this->push();
    lua_rawgeti(this->_thread, -1, i + 1);

    lua_CFunction res = lua_tocfunction(this->_thread, -1);
    lua_pop(this->_thread, 2);
    return res;
}

void LuaTable::setValue(const char *k, int validx)
{
    this->push();
    lua_pushvalue(this->_thread, validx);
    lua_setfield(this->_thread, -2, k);
    lua_pop(this->_thread, 1);
}

void LuaTable::setString(const char *k, const char *s)
{
    this->push();
    lua_pushstring(this->_thread, k);
    lua_pushstring(this->_thread, s);
    lua_rawset(this->_thread, -3);
    lua_pop(this->_thread, 1);
}

void LuaTable::setInteger(const char *k, lua_Integer n)
{
    this->push();
    lua_pushstring(this->_thread, k);
    lua_pushinteger(this->_thread, n);
    lua_rawset(this->_thread, -3);
    lua_pop(this->_thread, 1);
}

void LuaTable::setBoolean(const char *k, bool b)
{
    this->push();
    lua_pushstring(this->_thread, k);
    lua_pushboolean(this->_thread, b);
    lua_rawset(this->_thread, -3);
    lua_pop(this->_thread, 1);
}

void LuaTable::setTable(const char *k, LuaTable *t)
{
    this->push();
    lua_pushstring(this->_thread, k);
    t->push();
    lua_rawset(this->_thread, -3);
    lua_pop(this->_thread, 1);
}

void LuaTable::setFunction(const char *k, lua_CFunction f)
{
    this->push();
    lua_pushstring(this->_thread, k);
    lua_pushcfunction(this->_thread, f);
    lua_rawset(this->_thread, -3);
    lua_pop(this->_thread, 1);
}

void LuaTable::setI(int i, bool b)
{
    this->push();
    lua_pushboolean(this->_thread, b);
    lua_rawseti(this->_thread, -2, i);
    lua_pop(this->_thread, 1);
}

void LuaTable::setI(int i, const char *s)
{
    this->push();
    lua_pushstring(this->_thread, s);
    lua_rawseti(this->_thread, -2, i);
    lua_pop(this->_thread, 1);
}

void LuaTable::setI(int i, lua_Integer in)
{
    this->push();
    lua_pushinteger(this->_thread, in);
    lua_rawseti(this->_thread, -2, i);
    lua_pop(this->_thread, 1);
}

void LuaTable::setI(int i, lua_CFunction f)
{
    this->push();
    lua_pushcfunction(this->_thread, f);
    lua_rawseti(this->_thread, -2, i);
    lua_pop(this->_thread, 1);
}

void LuaTable::setI(int i, const LuaTable *t)
{
    this->push();
    t->push();
    lua_rawseti(this->_thread, -2, i);
    lua_pop(this->_thread, 1);
}

} // namespace Lua
} // namespace Core
} // namespace PrefLib

