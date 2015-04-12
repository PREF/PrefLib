#ifndef ARM64_H
#define ARM64_H

#include "../luacapstonemacros.h"
#include "../metadata.h"

namespace PrefLib {
namespace Core {
namespace Capstone {

void luaCS_pusharm64struct(lua_State* l, cs_arm64* arm64);

} // namespace Capstone
} // namespace Core
} // namespace PrefLib

#endif // ARM64_H

