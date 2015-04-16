#ifndef PREFLIB_CORE_LUA_LUATHREAD_H
#define PREFLIB_CORE_LUA_LUATHREAD_H

#include <stdexcept>
#include "luastate.h"

namespace PrefLib {
namespace Core {
namespace Lua {

class LuaThread
{
    public:
        LuaThread();
        ~LuaThread();

    public:
        void resume(int argc) const;
        operator lua_State*() const;

    private:
        lua_State* _thread;
};

} // namespace Lua
} // namespace Core
} // namespace PrefLib

#endif // PREFLIB_CORE_LUA_LUATHREAD_H
