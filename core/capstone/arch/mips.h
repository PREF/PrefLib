#ifndef MIPS_H
#define MIPS_H

#include "../luacapstonemacros.h"
#include "../metadata.h"

namespace PrefLib {
namespace Core {
namespace Capstone {

void luaCS_pushmipsstruct(lua_State* l, cs_mips* mips);

} // namespace Capstone
} // namespace Core
} // namespace PrefLib

#endif // MIPS_H

