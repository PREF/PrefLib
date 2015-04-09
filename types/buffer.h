#ifndef PREFLIB_BUFFER_H
#define PREFLIB_BUFFER_H

#include <cstdint>
#include <cstring>
#include "../core/luax.h"
#include "../core/luastate.h"
#include "../core/luareference.h"

namespace PrefLib {

using namespace Core;

class Buffer: public Core::LuaReference
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
