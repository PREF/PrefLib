#ifndef XCORE_H
#define XCORE_H

#include "../luacapstonemacros.h"
#include "../metadata.h"

namespace PrefLib {
namespace Core {
namespace Capstone {

void luaCS_pushxcorestruct(lua_State* l, cs_xcore* xcore);

} // namespace Capstone
} // namespace Core
} // namespace PrefLib

#endif // XCORE_H

