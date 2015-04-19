#include "pointer.h"

namespace PrefLib {
namespace Support {

Pointer::Pointer(uint64_t address, DataType::Type datatype, IO::DataBuffer* databuffer, lua_State* thread): LuaReference(thread)
{
    PointerData* pointerdata = reinterpret_cast<PointerData*>(lua_newuserdata(this->_thread, sizeof(PointerData)));
    pointerdata->Address = address;
    pointerdata->Type = datatype;
    pointerdata->DataBuffer = databuffer;

    if(luaL_newmetatable(this->_thread, "pointer"))
    {
        lua_pushcfunction(this->_thread, &Pointer::luaMetaIndex);
        lua_setfield(this->_thread, -2, "__index");
    }

    lua_setmetatable(this->_thread, -2);
    this->_reference = luaL_ref(this->_thread, LUA_REGISTRYINDEX);
}

Pointer::~Pointer()
{

}

int Pointer::luaMetaIndex(lua_State *l)
{
    PointerData* pointerdata = reinterpret_cast<PointerData*>(luaL_checkudata(l, 1, "pointer"));
    uint64_t span = luaL_checkinteger(l, 2) * DataType::sizeOf(pointerdata->Type);

    DataValue dv = pointerdata->DataBuffer->readType(pointerdata->Address + span, pointerdata->Type);
    dv.push(l);
    return 1;
}

} // namespace Support
} // namespace PrefLib

