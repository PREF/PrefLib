#include "luareference.h"

namespace PrefLib {
namespace Core {
namespace Lua {

LuaReference::LuaReference(lua_State *thread): _reference(LUA_REFNIL)
{
    this->_thread = (thread ? thread : LuaState::instance());
}

LuaReference::LuaReference(const LuaReference &lr)
{
    *this = lr;
}

LuaReference::~LuaReference()
{
    this->deleteReference();
}

void LuaReference::push() const
{
    lua_rawgeti(this->_thread, LUA_REGISTRYINDEX, this->_reference);
}

lua_State *LuaReference::moveTo(lua_State *to)
{
    if(this->_thread == to)
        return this->_thread;

    lua_State* oldthread = this->_thread;
    this->_thread = to;
    return oldthread;
}

lua_State *LuaReference::thread() const
{
    return this->_thread;
}

void LuaReference::deleteReference()
{
    if(this->_reference != LUA_REFNIL)
    {
        luaL_unref(this->_thread, LUA_REGISTRYINDEX, this->_reference);
        this->_reference = LUA_REFNIL;
    }
}

int LuaReference::cloneReference(const LuaReference &lr)
{
    if(lr._reference != LUA_REFNIL)
    {
        lr.push();
        return luaL_ref(this->_thread, LUA_REGISTRYINDEX);
    }

    return LUA_REFNIL;
}

LuaReference &LuaReference::operator=(const LuaReference &rhs)
{
    this->deleteReference();
    this->_thread = rhs._thread;
    this->_reference = this->cloneReference(rhs);
    return *this;
}

} // namespace Lua
} // namespace Core
} // namespace PrefLib

