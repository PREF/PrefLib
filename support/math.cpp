#include "math.h"

namespace PrefLib {
namespace Support {

Math::Math()
{

}

Math::~Math()
{

}

void Math::push(lua_State* l)
{
    lua_newtable(l);

    lua_pushcfunction(l, &Math::luaLogn);
    lua_setfield(l, -2, "logn");
}

double Math::logn(double n, unsigned int base)
{
    return log(n) / log(base);
}


int Math::luaLogn(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 2);

    lua_pushnumber(l, Math::logn(luaL_checknumber(l, 1), luaL_checknumber(l, 2)));
    return 1;
}

} // namespace Support
} // namespace PrefLib

