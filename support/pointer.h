#ifndef PREFLIB_SUPPORT_POINTER_H
#define PREFLIB_SUPPORT_POINTER_H

#include "../core/lua/luareference.h"
#include "../io/databuffer.h"
#include "../types/datatype.h"
#include "../types/datavalue.h"

namespace PrefLib {
namespace Support {

using namespace Core::Lua;

class Pointer: public LuaReference
{
    private:
        struct PointerData { uint64_t Address; DataType::Type Type; IO::DataBuffer* DataBuffer; };

    public:
        Pointer(uint64_t address, DataType::Type datatype, IO::DataBuffer* databuffer, lua_State* thread = nullptr);
        ~Pointer();

    lua_api:
        static int luaMetaIndex(lua_State* l);
};

} // namespace Support
} // namespace PrefLib

#endif // PREFLIB_SUPPORT_POINTER_H
