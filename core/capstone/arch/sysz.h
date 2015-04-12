#ifndef SYSZ_H
#define SYSZ_H

#include "../luacapstonemacros.h"
#include "../metadata.h"

namespace PrefLib {
namespace Core {
namespace Capstone {

void luaCS_pushsyszstruct(lua_State* l, cs_sysz* sysz);

} // namespace Capstone
} // namespace Core
} // namespace PrefLib

#endif // SYSZ_H

