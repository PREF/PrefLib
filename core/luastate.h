#ifndef PREFLIB_CORE_LUASTATE_H
#define PREFLIB_CORE_LUASTATE_H

#include <lua.hpp>

namespace PrefLib {
namespace Core {

class LuaState
{
    private:
        LuaState();

    public:
        static const LuaState& instance();
        void close() const;
        operator lua_State*() const;

    private:
        static LuaState _instance;
        lua_State* _state;
};

} // namespace Core
} // namespace PrefLib

#endif // PREFLIB_CORE_LUASTATE_H
