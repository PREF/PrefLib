#ifndef PREFLIB_CORE_LUA_LUATHREAD_H
#define PREFLIB_CORE_LUA_LUATHREAD_H

#include <map>
#include <stdexcept>
#include "luastate.h"
#include "luareference.h"

namespace PrefLib {
namespace Core {
namespace Lua {

class LuaThread
{
    public:
        LuaThread();
        ~LuaThread();

    public:
        void take(LuaReference* refobj);
        void resume(int argc) const;
        operator lua_State*() const;

    private:
        lua_State* _thread;
        std::map<LuaReference*, lua_State*> _objects;
};

} // namespace Lua
} // namespace Core
} // namespace PrefLib

#endif // PREFLIB_CORE_LUA_LUATHREAD_H
