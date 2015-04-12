#include "luareference.h"

namespace PrefLib {
namespace Core {
namespace Lua {

LuaReference::LuaReference(): _reference(LUA_REFNIL)
{

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
    lua_rawgeti(LuaState::instance(), LUA_REGISTRYINDEX, this->_reference);
}

void LuaReference::deleteReference()
{
    if(this->_reference != LUA_REFNIL)
    {
        luaL_unref(LuaState::instance(), LUA_REGISTRYINDEX, this->_reference);
        this->_reference = LUA_REFNIL;
    }
}

int LuaReference::cloneReference(const LuaReference &lr)
{
    if(lr._reference != LUA_REFNIL)
    {
        lr.push();
        return luaL_ref(LuaState::instance(), LUA_REGISTRYINDEX);
    }

    return LUA_REFNIL;
}

LuaReference &LuaReference::operator=(const LuaReference &rhs)
{
    this->deleteReference();
    this->_reference = this->cloneReference(rhs);
    return *this;
}

} // namespace Lua
} // namespace Core
} // namespace PrefLib

