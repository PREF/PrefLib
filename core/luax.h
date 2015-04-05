#ifndef LUAX_H
#define LUAX_H

#include <lua.hpp>

#define lua_api private

namespace PrefLib {
namespace Core {

/* Error Handling Functions */
inline void luaX_expectminargc(lua_State* l, int argc, int minexpected)
{
    if(argc >= minexpected)
        return;

    luaL_error(l, "Expected at least '%d' arguments, '%d' given", minexpected, argc);
}

inline void luaX_expectargc(lua_State* l, int argc, int expected)
{
    if(argc == expected)
        return;

     luaL_error(l, "Expected '%d' arguments, '%d' given", expected, argc);
}

} // namespace Core
} // namespace PrefLib

#endif // LUAX_H
