#ifndef PREFLIB_BUFFER_H
#define PREFLIB_BUFFER_H

#include <cstdint>
#include <cstring>
#include "../core/lua/luax.h"
#include "../core/lua/luastate.h"
#include "../core/lua/luareference.h"

namespace PrefLib {

using namespace Core::Lua;

class Buffer: public LuaReference
{
    public:
        Buffer(uint64_t len);
        unsigned char* operator &();

    lua_api:
        static int luaMetaIndex(lua_State* l);
        static int luaMetaNewIndex(lua_State* l);
        static int luaMetaLength(lua_State* l);

    private:
        unsigned char* _data;
};

} // namespace PrefLib

#endif // PREFLIB_BUFFER_H
