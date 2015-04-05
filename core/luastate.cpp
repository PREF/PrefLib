#include "luastate.h"

namespace PrefLib {
namespace Core {

LuaState LuaState::_instance;

LuaState::LuaState(): _state(nullptr)
{

}

const LuaState &LuaState::instance()
{
    if(!LuaState::_instance._state)
        LuaState::_instance._state = luaL_newstate();

    return LuaState::_instance;
}

void LuaState::close() const
{
    if(this->_state)
        lua_close(this->_state);
}

PrefLib::Core::LuaState::operator lua_State *() const
{
    return this->_state;
}

} // namespace Core
} // namespace PrefLib

