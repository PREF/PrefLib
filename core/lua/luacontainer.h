#ifndef PREFLIB_CORE_LUACONTAINER_H
#define PREFLIB_CORE_LUACONTAINER_H

#include "luatable.h"

namespace PrefLib {
namespace Core {
namespace Lua {

class LuaContainer: public LuaTable
{
    private:
        class Entry
        {
            public:
                Entry(LuaContainer& owner, lua_Integer idx): _owner(owner), _integerkey(true) { this->_tablekey.Index = idx; }
                Entry(LuaContainer& owner, const char* key): _owner(owner), _integerkey(false) { this->_tablekey.Key = key; }

            public:
                operator bool() const { return (this->_integerkey ? this->_owner.getI<bool>(this->_tablekey.Index) : this->_owner.getBoolean(this->_tablekey.Key)); }
                operator const char*() const { return (this->_integerkey ? this->_owner.getI<const char*>(this->_tablekey.Index) : this->_owner.getString(this->_tablekey.Key)); }
                operator lua_Integer() const { return (this->_integerkey ? this->_owner.getI<lua_Integer>(this->_tablekey.Index) : this->_owner.getInteger(this->_tablekey.Key)); }
                operator lua_CFunction() const { return (this->_integerkey ? this->_owner.getI<lua_CFunction>(this->_tablekey.Index) : this->_owner.getFunction(this->_tablekey.Key)); }
                operator LuaTable*() const { return (this->_integerkey ? this->_owner.bindedTable(this->_tablekey.Index) : this->_owner.getTable(this->_tablekey.Key)); }

            public:
                LuaContainer& operator =(bool val) { (this->_integerkey ? this->_owner.setI(this->_tablekey.Index, val) : this->_owner.setBoolean(this->_tablekey.Key, val)); return this->_owner; }
                LuaContainer& operator =(const char* val) { (this->_integerkey ? this->_owner.setI(this->_tablekey.Index, val) : this->_owner.setString(this->_tablekey.Key, val)); return this->_owner; }
                LuaContainer& operator =(lua_Integer val) { (this->_integerkey ? this->_owner.setI(this->_tablekey.Index, val) : this->_owner.setInteger(this->_tablekey.Key, val)); return this->_owner; }
                LuaContainer& operator =(lua_CFunction val) { (this->_integerkey ? this->_owner.setI(this->_tablekey.Index, val) : this->_owner.setFunction(this->_tablekey.Key, val)); return this->_owner; }
                LuaContainer& operator =(LuaTable* val)  { (this->_integerkey ? this->_owner.setI(this->_tablekey.Index, val) : this->_owner.setTable(this->_tablekey.Key, val)); return this->_owner; }

            private:
                LuaContainer& _owner;
                bool _integerkey;
                union { lua_Integer Index; const char* Key; } _tablekey;
        };

    public:
        LuaContainer(lua_State* thread = nullptr);
        ~LuaContainer();

    public:
        void append(bool val);
        void append(const char* val);
        void append(lua_Integer val);
        void append(lua_CFunction val);
        void append(LuaTable* val);
        LuaContainer::Entry operator[](lua_Integer idx);
        LuaContainer::Entry operator[](const char* key);
};

} // namespace Lua
} // namespace Core
} // namespace PrefLib

#endif // PREFLIB_CORE_LUACONTAINER_H
