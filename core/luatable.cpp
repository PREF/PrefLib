#include "luatable.h"

namespace PrefLib {
namespace Core {

LuaTable::LuaTable(): LuaReference()
{
    lua_State* l = LuaState::instance();
    lua_newtable(l);

    lua_pushstring(l, SELF_FIELD);
    lua_pushlightuserdata(l, this);
    lua_rawset(l, -3);

    this->_reference = luaL_ref(l, LUA_REGISTRYINDEX);
}

LuaTable::LuaTable(int idx): LuaReference()
{
    lua_State* l = LuaState::instance();
    lua_pushvalue(l, idx);

    lua_pushstring(l, SELF_FIELD);
    lua_pushlightuserdata(l, this);
    lua_rawset(l, -3);
    this->_reference = luaL_ref(l, LUA_REGISTRYINDEX);
}

LuaTable::~LuaTable()
{

}

LuaTable *LuaTable::bindedTable(int i) const
{
    lua_State* l = LuaState::instance();
    LuaTable* t = nullptr;

    this->push();
    lua_rawgeti(l, -1, i + 1);

    if(!lua_isnoneornil(l, -1))
        t = reinterpret_cast<LuaTable*>(checkThis(l, -1));

    lua_pop(l, 2);
    return t;
}

LuaTable *LuaTable::bindedTable(const char *name) const
{
    lua_State* l = LuaState::instance();
    LuaTable* t = nullptr;

    this->push();
    lua_pushstring(l, name);
    lua_rawget(l, -2);

    if(!lua_isnoneornil(l, -1))
        t = reinterpret_cast<LuaTable*>(checkThis(l, -1));

    lua_pop(l, 2);
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
    lua_State* l = LuaState::instance();

    this->push();
    this->setTable(name, t); // Allow self.foo
    this->setI(this->length() + 1, t); // Allow self[i]
    lua_pop(l, 1);
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
    lua_State* l = LuaState::instance();

    this->push();
    size_t len = lua_rawlen(l, -1);

    lua_pop(l, 1);
    return len;
}

void LuaTable::protectedCall(int nargs, int nres) const
{
    lua_State* l = LuaState::instance();
    int res = lua_pcall(l, nargs, nres, 0);

    if(res)
    {
        throw PrefException(lua_tostring(l, -1));
        lua_pop(l, 1);
    }
}

bool LuaTable::hasField(const char *k) const
{
    lua_State* l = LuaState::instance();
    bool res = false;

    this->push();
    lua_pushstring(l, k);
    lua_rawget(l, -2);

    res = !lua_isnoneornil(l, -1);
    lua_pop(l, 2);
    return res;
}

const char *LuaTable::getString(const char *k) const
{
    lua_State* l = LuaState::instance();

    this->push();
    lua_pushstring(l, k);
    lua_rawget(l, -2);

    const char* res = lua_tostring(l, -1);
    lua_pop(l, 2);
    return res;
}

lua_Integer LuaTable::getInteger(const char *k) const
{
    lua_State* l = LuaState::instance();

    this->push();
    lua_pushstring(l, k);
    lua_rawget(l, -2);

    lua_Integer res = lua_tointeger(l, -1);
    lua_pop(l, 2);
    return res;
}

LuaTable *LuaTable::getTable(const char *k) const
{
    lua_State* l = LuaState::instance();

    this->push();
    lua_pushstring(l, k);
    lua_rawget(l, -2);

    LuaTable* res = reinterpret_cast<LuaTable*>(checkThis(l, -1));
    lua_pop(l, 2);
    return res;
}

lua_CFunction LuaTable::getFunction(const char *k) const
{
    lua_State* l = LuaState::instance();

    this->push();
    lua_pushstring(l, k);
    lua_rawget(l, -2);

    lua_CFunction res = lua_tocfunction(l, -1);
    lua_pop(l, 2);
    return res;
}

template<> const char* LuaTable::getI<const char*>(int i) const
{
    lua_State* l = LuaState::instance();

    this->push();
    lua_rawgeti(l, -1, i);

    const char* res = lua_tostring(l, -1);
    lua_pop(l, 2);
    return res;
}

template<> lua_Integer LuaTable::getI<lua_Integer>(int i) const
{
    lua_State* l = LuaState::instance();

    this->push();
    lua_rawgeti(l, -1, i);

    lua_Integer res = lua_tointeger(l, -1);
    lua_pop(l, 2);
    return res;
}

template<> LuaTable* LuaTable::getI<LuaTable*>(int i) const
{
    lua_State* l = LuaState::instance();

    this->push();
    lua_rawgeti(l, -1, i);

    LuaTable* res = reinterpret_cast<LuaTable*>(checkThis(l, -1));
    lua_pop(l, 2);
    return res;
}

template<> lua_CFunction LuaTable::getI<lua_CFunction>(int i) const
{
    lua_State* l = LuaState::instance();

    this->push();
    lua_rawgeti(l, -1, i);

    lua_CFunction res = lua_tocfunction(l, -1);
    lua_pop(l, 2);
    return res;
}

void LuaTable::setValue(const char *k, int validx)
{
    lua_State* l = LuaState::instance();

    this->push();
    lua_pushvalue(l, validx);
    lua_setfield(l, -2, k);
    lua_pop(l, 1);
}

void LuaTable::setString(const char *k, const char *s)
{
    lua_State* l = LuaState::instance();

    this->push();
    lua_pushstring(l, k);
    lua_pushstring(l, s);
    lua_rawset(l, -3);
    lua_pop(l, 1);
}

void LuaTable::setInteger(const char *k, lua_Integer n)
{
    lua_State* l = LuaState::instance();

    this->push();
    lua_pushstring(l, k);
    lua_pushinteger(l, n);
    lua_rawset(l, -3);
    lua_pop(l, 1);
}

void LuaTable::setTable(const char *k, LuaTable *t)
{
    lua_State* l = LuaState::instance();

    this->push();
    lua_pushstring(l, k);
    t->push();
    lua_rawset(l, -3);
    lua_pop(l, 1);
}

void LuaTable::setFunction(const char *k, lua_CFunction f)
{
    lua_State* l = LuaState::instance();

    this->push();
    lua_pushstring(l, k);
    lua_pushcfunction(l, f);
    lua_rawset(l, -3);
    lua_pop(l, 1);
}

void LuaTable::setI(int i, const LuaTable *t)
{
    lua_State* l = LuaState::instance();

    this->push();
    t->push();
    lua_rawseti(l, -2, i);
    lua_pop(l, 1);
}

} // namespace Core
} // namespace PrefLib

