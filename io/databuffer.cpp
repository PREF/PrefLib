#include "databuffer.h"

namespace PrefLib {
namespace IO {

DataBuffer::DataBuffer(OpenMode mode, lua_State *thread): LuaTable(thread)
{
    this->setBoolean("readable", ((mode & OpenMode::Read) != 0));
    this->setBoolean("writable", ((mode & OpenMode::Write) != 0));
    this->setFunction("at", &DataBuffer::luaAt);
    this->setFunction("copyTo", &DataBuffer::luaCopyTo);
    this->setFunction("read", &DataBuffer::luaRead);
    this->setFunction("write", &DataBuffer::luaWrite);

    lua_State* l = LuaState::instance();
    this->push();

    if(luaL_newmetatable(l, "databuffer"))
    {
        lua_pushcfunction(l, &DataBuffer::luaMetaLength);
        lua_setfield(l, -2, "__len");
    }

    lua_setmetatable(l, -2);
    lua_pop(l, 1);
}

DataBuffer::~DataBuffer()
{

}

bool DataBuffer::isReadable() const
{
    return this->getBoolean("readable");
}

bool DataBuffer::isWritable() const
{
    return this->getBoolean("writable");
}

unsigned char DataBuffer::at(uint64_t offset)
{
    unsigned char ch = '\0';
    this->read(offset, &ch, 1);
    return ch;
}

void DataBuffer::copyTo(DataBuffer *destbuffer, uint64_t startoffset, uint64_t endoffset)
{
    if(!endoffset)
        endoffset = this->length();

    uint64_t len = endoffset - startoffset;
    unsigned char* data = new unsigned char[len];

    this->read(startoffset, data, len);
    destbuffer->write(0, data, len);

    delete[] data;
}

int DataBuffer::luaAt(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 2);

    DataBuffer* thethis = reinterpret_cast<DataBuffer*>(checkThis(l, 1));
    lua_pushinteger(l, thethis->at(luaL_checkinteger(l, 2)));
    return 1;
}

int DataBuffer::luaCopyTo(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectminargc(l, argc, 2);

    DataBuffer* thethis = reinterpret_cast<DataBuffer*>(checkThis(l, 1));
    thethis->copyTo(reinterpret_cast<DataBuffer*>(checkThis(l, 2)), luaL_optinteger(l, 3, 0), luaL_optinteger(l, 4, 0));
    return 0;
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

