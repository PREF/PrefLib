#ifndef PREFLIB_SUPPORT_MATH_H
#define PREFLIB_SUPPORT_MATH_H

#include <cmath>
#include "../core/lua/luax.h"
#include "../core/lua/luatable.h"

namespace PrefLib {
namespace Support {

using namespace Core::Lua;

class Math
{
    private:
        Math();
        ~Math();

    public:
        static void push(lua_State *l);

    public:
        static double logn(double n, unsigned int base);

    lua_api:
        static int luaLogn(lua_State* l);
};

} // namespace Support
} // namespace PrefLib

#endif // PREFLIB_SUPPORT_MATH_H
