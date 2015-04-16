#ifndef PREFLIB_CORE_LUAREFERENCE_H
#define PREFLIB_CORE_LUAREFERENCE_H

#include <stdexcept>
#include "luastate.h"

namespace PrefLib {
namespace Core {
namespace Lua {

class LuaReference
{
    public:
        LuaReference(lua_State* thread = nullptr);
        LuaReference(const LuaReference& lr);
        virtual ~LuaReference();
        virtual void push() const;
        lua_State* moveTo(lua_State* to);
        lua_State* thread() const;

    private:
        void deleteReference();
        int cloneReference(const LuaReference& lr);

    public:
        LuaReference& operator=(const LuaReference& rhs);

    protected:
        lua_State* _thread;
        int _reference;
};

} // namespace Lua
} // namespace Core
} // namespace PrefLib

#endif // PREFLIB_CORE_LUAREFERENCE_H
