#ifndef PREFLIB_CORE_LUATABLE_H
#define PREFLIB_CORE_LUATABLE_H

#include <stdexcept>
#include "luareference.h"

#define SELF_FIELD "__self"

namespace PrefLib {
namespace Core {
namespace Lua {

class LuaTable: public LuaReference
{
    public:
        LuaTable(lua_State* thread = nullptr);
        LuaTable(lua_State *thread, int idx);
        virtual ~LuaTable();

    protected:
        void unbindTable(int i, const char* name) const;
        LuaTable* bindedTable(int i) const;
        LuaTable* bindedTable(const char* name) const;
        LuaTable* firstBindedTable() const;
        LuaTable* lastBindedTable();
        void bindTable(const char* name, LuaTable* t);

    public:
        static void* checkThis(lua_State* l, int idx);
        virtual size_t length() const;
        void protectedCall(int nargs, int nres) const;
        bool hasField(const char* k) const;
        bool hasField(lua_Integer i) const;
        const char* getString(const char* k) const;
        const char* getString(lua_Integer k) const;
        lua_Integer getInteger(const char* k) const;
        lua_Integer getInteger(lua_Integer k) const;
        bool getBoolean(const char* k) const;
        bool getBoolean(lua_Integer k) const;
        LuaTable* getTable(const char* k) const;
        LuaTable* getTable(lua_Integer k) const;
        lua_CFunction getFunction(const char* k) const;
        lua_CFunction getFunction(lua_Integer k) const;
        template<typename T> T getI(lua_Integer i) const;
        void setValue(const char* k, int validx);
        void setValue(lua_Integer k, int validx);
        void setString(const char* k, const char* s);
        void setString(lua_Integer k, const char* s);
        void setInteger(const char* k, lua_Integer n);
        void setInteger(lua_Integer k, lua_Integer n);
        void setBoolean(const char* k, bool b);
        void setBoolean(lua_Integer k, bool b);
        void setTable(const char* k, LuaTable* t);
        void setTable(lua_Integer k, LuaTable* t);
        void setFunction(const char* k, lua_CFunction f);
        void setFunction(lua_Integer k, lua_CFunction f);
};

} // namespace Lua
} // namespace Core
} // namespace PrefLib

#endif // PREFLIB_CORE_LUATABLE_H
