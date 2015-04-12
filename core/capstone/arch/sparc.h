#ifndef SPARC_H
#define SPARC_H

#include "../luacapstonemacros.h"
#include "../metadata.h"

namespace PrefLib {
namespace Core {
namespace Capstone {

void luaCS_pushsparcstruct(lua_State* l, cs_sparc* sparc);

} // namespace Capstone
} // namespace Core
} // namespace PrefLib

#endif // SPARC_H

