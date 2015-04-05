#include "databuffer.h"

namespace PrefLib {
namespace IO {

DataBuffer::Buffer::Buffer(uint64_t len): Core::LuaReference()
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

unsigned char *DataBuffer::Buffer::operator &()
{
    return this->_data;
}

int DataBuffer::Buffer::luaMetaIndex(lua_State *l)
{
    unsigned char* data = reinterpret_cast<unsigned char*>(lua_touserdata(l, 1));
    int len = lua_tointeger(l, lua_upvalueindex(1)), idx = luaL_checkinteger(l, 2) - 1;

    if((idx < 0) || (idx >= len))
    {
        lua_pushstring(l, "Buffer.__newindex: Index out of range");
        lua_error(l);
        return 0;
    }

    lua_pushinteger(l, data[idx]);
    return 1;
}

int DataBuffer::Buffer::luaMetaNewIndex(lua_State *l)
{
    unsigned char* data = reinterpret_cast<unsigned char*>(lua_touserdata(l, 1));
    int len = lua_tointeger(l, lua_upvalueindex(1)), idx = luaL_checkinteger(l, 2) - 1;

    if((idx < 0) || (idx >= len))
    {
        lua_pushstring(l, "Buffer.__newindex: Index out of range");
        lua_error(l);
        return 0;
    }

    data[idx] = static_cast<unsigned char>(luaL_checkinteger(l, 3));
    return 0;
}

int DataBuffer::Buffer::luaMetaLength(lua_State *l)
{
    lua_pushvalue(l, lua_upvalueindex(1));
    return 1;
}

DataBuffer::DataBuffer(): Core::LuaTable()
{
    lua_State* l = LuaState::instance();
    this->push();

    if(luaL_newmetatable(l, "databuffer"))
    {
        lua_pushcfunction(l, &DataBuffer::luaMetaLength);
        lua_setfield(l, -2, "__len");
    }

    lua_setmetatable(l, -2);
    this->setFunction("at", &DataBuffer::luaAt);
    this->setFunction("read", &DataBuffer::luaRead);
    this->setFunction("write", &DataBuffer::luaWrite);
    lua_pop(l, 1);
}

DataBuffer::~DataBuffer()
{

}

unsigned char DataBuffer::at(uint64_t offset)
{
    unsigned char ch = '\0';
    this->read(offset, &ch, 1);
    return ch;
}

int DataBuffer::luaAt(lua_State *l)
{
    DataBuffer* thethis = reinterpret_cast<DataBuffer*>(checkThis(l, 1));
    uint64_t offset = luaL_checkinteger(l, 2);

    lua_pushinteger(l, thethis->at(offset));
    return 1;
}

int DataBuffer::luaMetaLength(lua_State *l)
{
    DataBuffer* thethis = reinterpret_cast<DataBuffer*>(checkThis(l, 1));

    lua_pushinteger(l, thethis->length());
    return 1;
}

int DataBuffer::luaRead(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 3);

    DataBuffer* thethis = reinterpret_cast<DataBuffer*>(checkThis(l, 1));
    uint64_t offset = std::max(luaL_checkinteger(l, 2), static_cast<lua_Integer>(0));
    uint64_t len = std::max(luaL_checkinteger(l, 3), static_cast<lua_Integer>(0));

    Buffer buffer(len);
    thethis->read(offset, &buffer, len);
    buffer.push();
    return 1;
}

int DataBuffer::luaWrite(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectminargc(l, argc, 3);

    DataBuffer* thethis = reinterpret_cast<DataBuffer*>(checkThis(l, 1));
    uint64_t offset = std::max(luaL_checkinteger(l, 2), static_cast<lua_Integer>(0));

    int t = lua_type(l, 3);
    unsigned char* data = nullptr;
    uint64_t len = 0;

    if((t != LUA_TUSERDATA) && (t == LUA_TTABLE))
        luaL_error(l, "DataBuffer.write(): Expected 'userdata' or 'table' type, %s given", lua_typename(l, t));
    else
    {
        if(t == LUA_TTABLE)
        {
            len = lua_rawlen(l, 3);

            if(len <= 0)
                return 0;

            data = new unsigned char[len];

            for(uint64_t i = 0; i < len; i++)
            {
                lua_geti(l, 3, i + 1);
                data[i] = static_cast<unsigned char>(lua_tointeger(l, -1));
                lua_pop(l, 1);
            }
        }
        else // if(t == LUA_TUSERDATA)
        {
            lua_len(l, 3);
            len = lua_tointeger(l, -1);
            lua_pop(l, 1);

            data = reinterpret_cast<unsigned char*>(lua_touserdata(l, 3));
        }

        thethis->write(offset, data, len);
    }

    return 0;
}

} // namespace IO
} // namespace PrefLib

