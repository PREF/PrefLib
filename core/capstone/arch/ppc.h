#ifndef PPC_H
#define PPC_H

#include "../luacapstonemacros.h"
#include "../metadata.h"

namespace PrefLib {
namespace Core {
namespace Capstone {

void luaCS_pushppcstruct(lua_State* l, cs_ppc* ppc);

} // namespace Capstone
} // namespace Core
} // namespace PrefLib

#endif // PPC_H

