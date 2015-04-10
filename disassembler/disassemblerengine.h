#ifndef PREFLIB_DISASSEMBLER_DISASSEMBLERENGINE_H
#define PREFLIB_DISASSEMBLER_DISASSEMBLERENGINE_H

#include <deque>
#include "../core/luax.h"
#include "../core/luatable.h"
#include "disassemblerdefinition.h"
#include "disassemblerlisting.h"

namespace PrefLib {
namespace Disassembler {

class DisassemblerEngine: public LuaTable
{
    public:
        DisassemblerEngine(DisassemblerDefinition* definition);
        ~DisassemblerEngine();
        void disassemble(DisassemblerListing* listing);

    private:
        void prepareStack(DisassemblerListing* listing);

    lua_api:
        static int luaNext(lua_State* l);
        static int luaEnqueue(lua_State* l);

    private:
        DisassemblerDefinition* _definition;
        std::deque<DataValue> _queue;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_DISASSEMBLERENGINE_H
