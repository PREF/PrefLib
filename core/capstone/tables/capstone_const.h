#ifndef CAPSTONE_CONST_H
#define CAPSTONE_CONST_H

#include <lua.hpp>
#include <capstone.h>

namespace PrefLib {
namespace Core {
namespace Capstone {

void set_capstone_const(lua_State* l);

} // namespace Capstone
} // namespace Core
} // namespace PrefLib

#endif // CAPSTONE_CONST_H

