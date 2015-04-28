#ifndef PREFLIB_CORE_LUACONTAINER_H
#define PREFLIB_CORE_LUACONTAINER_H

#include <cmath>
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

        template<typename K, typename T> struct BinaryComparator
        {
            lua_Integer operator()(const K& k, const T& t)
            {
                if(k > t)
                    return 1;

                if(k < t)
                    return -1;

                return 0;
            }
        };

    public:
        LuaContainer(lua_State* thread = nullptr);
        ~LuaContainer();

    private:
        void pushMethod(const char* method);

    public:
        void append(bool val);
        void append(const char* val);
        void append(lua_Integer val);
        void append(lua_CFunction val);
        void append(LuaTable* val);
        void insert(lua_Integer idx, bool val);
        void insert(lua_Integer idx, const char* val);
        void insert(lua_Integer idx, lua_Integer val);
        void insert(lua_Integer idx, lua_CFunction val);
        void insert(lua_Integer idx, LuaTable* val);
        void remove(lua_Integer idx);
        void removeKey(const char* key);
        void removeKey(lua_Integer key);
        bool isEmpty() const;
        LuaContainer::Entry operator[](const char* key);
        LuaContainer::Entry operator[](lua_Integer idx);

    public:
        template<typename T> T first() const;
        template<typename T> T last() const;
        template<typename T, typename C = std::less<T> > void binaryInsert(const T& t);
        template<typename K, typename T = K, typename C = BinaryComparator<K, T> > lua_Integer binarySearch(const K& k, bool reversed = false);
};

template<typename T> T LuaContainer::first() const
{
    return this->getI<T>(0);
}

template<typename T> T LuaContainer::last() const
{
    return this->getI<T>(this->length() - 1);
}

template<typename T, typename C> void LuaContainer::binaryInsert(const T& t)
{
    lua_Integer start = 0, end = this->length() - 1, mid = 0, state = 0;
    C comparator = C();

    while(start <= end)
    {
        mid = std::floor((start + end) / 2);

        if(comparator(t, this->getI<T>(mid)))
        {
            end = mid - 1;
            state = 0;
        }
        else
        {
            start = mid + 1;
            state = 1;
        }
    }

    this->insert(mid + state, t);
}

template<typename K, typename T, typename C> lua_Integer LuaContainer::binarySearch(const K& k, bool reversed)
{
    lua_Integer start = 0, end = this->length() - 1, mid = 0;
    C comparator = C();

    while(start <= end)
    {
        mid = std::floor((start + end) / 2);
        lua_Integer comp = comparator(k, this->getI<T>(mid));

        if(comp > 0)
        {
            if(reversed)
                end = mid - 1;
            else
                start = mid + 1;
        }
        else if(comp < 0)
        {
            if(reversed)
                start = mid + 1;
            else
                end = mid - 1;
        }
        else
            return mid;
    }

    return -1;
}

} // namespace Lua
} // namespace Core
} // namespace PrefLib

#endif // PREFLIB_CORE_LUACONTAINER_H
