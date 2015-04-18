#ifndef PREFLIB_IO_DATABUFFER_H
#define PREFLIB_IO_DATABUFFER_H

#include <algorithm>
#include <cstdint>
#include <cctype>
#include "../types/datavalue.h"
#include "../types/buffer.h"
#include "../core/lua/luax.h"
#include "../core/lua/luatable.h"

namespace PrefLib {
namespace IO {

using namespace Core::Lua;

class DataBuffer : public LuaTable
{
    public:
        enum OpenMode { Read = 1, Write = 2, ReadWrite = Read | Write };

    public:
        DataBuffer(OpenMode mode, lua_State* thread = nullptr);
        ~DataBuffer();
        bool isReadable() const;
        bool isWritable() const;

    public:
        unsigned char at(uint64_t offset);
        int64_t indexOf(const char* s, uint64_t startoffset = 0);
        uint64_t readString(uint64_t offset, char** data, uint64_t maxlen = 0);
        uint64_t readLine(uint64_t offset, char** data);
        DataValue readType(uint64_t offset, DataType::Type datatype);
        void copyTo(DataBuffer* destbuffer, uint64_t startoffset = 0, uint64_t endoffset = 0);

    public: /* Abstract Methods */
        virtual uint64_t length() const = 0;
        virtual uint64_t read(uint64_t offset, unsigned char* data, uint64_t len) = 0;
        virtual uint64_t write(uint64_t offset, const unsigned char* data, uint64_t len) = 0;

    lua_api:
        static int luaMetaLength(lua_State* l);
        static int luaAt(lua_State* l);
        static int luaIndexOf(lua_State* l);
        static int luaReadString(lua_State* l);
        static int luaReadLine(lua_State* l);
        static int luaReadType(lua_State* l);
        static int luaCopyTo(lua_State* l);
        static int luaRead(lua_State* l);
        static int luaWrite(lua_State* l);
};

} // namespace IO
} // namespace PrefLib

#endif // PREFLIB_IO_DATABUFFER_H
