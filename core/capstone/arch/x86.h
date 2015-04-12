#ifndef X86_H
#define X86_H

#include "../luacapstonemacros.h"
#include "../metadata.h"

namespace PrefLib {
namespace Core {
namespace Capstone {

void luaCS_pushx86struct(lua_State* l, cs_x86* x86);

} // namespace Capstone
} // namespace Core
} // namespace PrefLib

#endif // X86_H

