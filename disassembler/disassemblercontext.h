#ifndef PREFLIB_DISASSEMBLER_DISASSEMBLERCONTEXT_H
#define PREFLIB_DISASSEMBLER_DISASSEMBLERCONTEXT_H

#include "../core/luax.h"
#include "../core/luatable.h"
#include "disassemblerdefinition.h"

namespace PrefLib {
namespace Disassembler {

using namespace Core;

class DisassemblerContext: public LuaTable
{
    public:
        DisassemblerContext();
        ~DisassemblerContext();

    public:
        DisassemblerDefinition* get(int idx) const;

    lua_api:
        static int luaCreate(lua_State *l);
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_DISASSEMBLERCONTEXT_H
