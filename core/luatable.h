#ifndef PREFLIB_CORE_LUATABLE_H
#define PREFLIB_CORE_LUATABLE_H

#include <stdexcept>
#include "luareference.h"

#define SELF_FIELD "__self"

namespace PrefLib {
namespace Core {

class LuaTable: public LuaReference
{
    public:
        LuaTable();
        LuaTable(int idx);
        virtual ~LuaTable();

    protected:
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
        lua_Integer getInteger(const char* k) const;
        bool getBoolean(const char* k) const;
        LuaTable* getTable(const char* k) const;
        lua_CFunction getFunction(const char* k) const;
        template<typename T> T getI(int i) const;
        void setValue(const char* k, int validx);
        void setString(const char* k, const char* s);
        void setInteger(const char* k, lua_Integer n);
        void setBoolean(const char* k, bool b);
        void setTable(const char* k, LuaTable* t);
        void setFunction(const char* k, lua_CFunction f);
        void setI(int i, bool b);
        void setI(int i, const char *s);
        void setI(int i, lua_Integer in);
        void setI(int i, lua_CFunction f);
        void setI(int i, const LuaTable *t);
};

template<typename T> T LuaTable::getI(int) const
{
    throw std::runtime_error("LuaTable::getI(): Unsupported Type");
}

} // namespace Core
} // namespace PrefLib

#endif // PREFLIB_CORE_LUATABLE_H
