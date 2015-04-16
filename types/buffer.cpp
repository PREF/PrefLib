#include "buffer.h"

namespace PrefLib {

Buffer::Buffer(uint64_t len, lua_State *thread): LuaReference(thread)
{
    lua_State* l = LuaState::instance();
    this->_data = reinterpret_cast<unsigned char*>(lua_newuserdata(l, len * sizeof(unsigned char)));

    if(luaL_newmetatable(l, "buffer"))
    {
        lua_pushinteger(l, len);
        lua_pushcclosure(l, &Buffer::luaMetaIndex, 1);
        lua_setfield(l, -2, "__index");

        lua_pushinteger(l, len);
        lua_pushcclosure(l, &Buffer::luaMetaNewIndex, 1);
        lua_setfield(l, -2, "__newindex");

        lua_pushinteger(l, len);
        lua_pushcclosure(l, &Buffer::luaMetaLength, 1);
        lua_setfield(l, -2, "__len");
    }

    lua_setmetatable(l, -2);
    this->_reference = luaL_ref(l, LUA_REGISTRYINDEX);
}

unsigned char *Buffer::operator &()
{
    return this->_data;
}

int Buffer::luaMetaIndex(lua_State *l)
{
    unsigned char* data = reinterpret_cast<unsigned char*>(lua_touserdata(l, 1));
    lua_Integer len = lua_tointeger(l, lua_upvalueindex(1));

    if(lua_type(l, 2) == LUA_TSTRING)
    {
        if(!strcmp(lua_tostring(l, 2), "address"))
        {
            lua_pushlightuserdata(l, data);
            return 1;
        }

        return 0;
    }

    lua_Integer idx = luaL_checkinteger(l, 2) - 1;

    if((idx < 0) || (idx >= len))
    {
        lua_pushstring(l, "Buffer.__newindex: Index out of range");
        lua_error(l);
        return 0;
    }

    lua_pushinteger(l, data[idx]);
    return 1;
}

int Buffer::luaMetaNewIndex(lua_State *l)
{
    unsigned char* data = reinterpret_cast<unsigned char*>(lua_touserdata(l, 1));
    lua_Integer len = lua_tointeger(l, lua_upvalueindex(1)), idx = luaL_checkinteger(l, 2) - 1;

    if((idx < 0) || (idx >= len))
    {
        lua_pushstring(l, "Buffer.__newindex: Index out of range");
        lua_error(l);
        return 0;
    }

    data[idx] = static_cast<unsigned char>(luaL_checkinteger(l, 3));
    return 0;
}

int Buffer::luaMetaLength(lua_State *l)
{
    lua_pushvalue(l, lua_upvalueindex(1));
    return 1;
}

} // namespace PrefLib

