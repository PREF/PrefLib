#ifndef ARM_H
#define ARM_H

#include "../luacapstonemacros.h"
#include "../metadata.h"

namespace PrefLib {
namespace Core {
namespace Capstone {

void luaCS_pusharmstruct(lua_State* l, cs_arm* arm);

} // namespace Capstone
} // namespace Core
} // namespace PrefLib

#endif // ARM_H
