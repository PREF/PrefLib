#include "luathread.h"

namespace PrefLib {
namespace Core {
namespace Lua {

LuaThread::LuaThread()
{
    this->_thread = lua_newthread(LuaState::instance());
}

LuaThread::~LuaThread()
{
    std::map<LuaReference*, lua_State*>::iterator it = this->_objects.begin();

    for(; it != this->_objects.end(); it++)
        it->first->_thread = it->second;

    this->_objects.clear();
    lua_pop(LuaState::instance(), 1);
    this->_thread = nullptr;
}

void LuaThread::take(LuaReference *refobj)
{
    if(refobj->_thread == this->_thread)
        return;

    this->_objects[refobj] = refobj->_thread;
    refobj->_thread = this->_thread;
}

void LuaThread::resume(int argc) const
{
    int res = lua_resume(this->_thread, nullptr, argc);

    if(res)
    {
        throw std::runtime_error(lua_tostring(this->_thread, -1));
        lua_pop(this->_thread, argc + 1);
    }
}

LuaThread::operator lua_State*() const
{
    return this->_thread;
}

} // namespace Lua
} // namespace Core
} // namespace PrefLib

