#ifndef PREFLIB_DISASSEMBLER_DISASSEMBLERCONTEXT_H
#define PREFLIB_DISASSEMBLER_DISASSEMBLERCONTEXT_H

#include "../core/lua/luax.h"
#include "../core/lua/luatable.h"
#include "disassemblerdefinition.h"
#include "blocks/segment.h"

namespace PrefLib {
namespace Disassembler {

using namespace Core;

class DisassemblerContext: public LuaTable
{
    public:
        DisassemblerContext();
        ~DisassemblerContext();

    public:
        virtual void push() const;
        DisassemblerDefinition* get(int idx) const;

    lua_api:
        static int luaCreate(lua_State *l);
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_DISASSEMBLERCONTEXT_H
