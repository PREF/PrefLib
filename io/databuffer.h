#ifndef PREFLIB_IO_DATABUFFER_H
#define PREFLIB_IO_DATABUFFER_H

#include <algorithm>
#include <cstdint>
#include "../types/datavalue.h"
#include "../core/luax.h"
#include "../core/luatable.h"

namespace PrefLib {
namespace IO {

using namespace Core;

class DataBuffer : public Core::LuaTable
{
    private:
        class Buffer: public Core::LuaReference
        {
            public:
                Buffer(uint64_t len);
                unsigned char* operator &();

            private:
                static int luaMetaIndex(lua_State* l);
                static int luaMetaNewIndex(lua_State* l);
                static int luaMetaLength(lua_State* l);

            private:
                unsigned char* _data;
        };

    public:
        DataBuffer();
        ~DataBuffer();

    public:
        unsigned char at(uint64_t offset);

    public: /* Abstract Methods */
        virtual uint64_t length() const = 0;
        virtual int read(uint64_t offset, unsigned char* data, uint64_t len) = 0;
        virtual int write(uint64_t offset, const unsigned char* data, uint64_t len) = 0;

    lua_api:
        static int luaMetaLength(lua_State* l);
        static int luaAt(lua_State* l);
        static int luaRead(lua_State* l);
        static int luaWrite(lua_State* l);
};

} // namespace IO
} // namespace PrefLib

#endif // PREFLIB_IO_DATABUFFER_H
