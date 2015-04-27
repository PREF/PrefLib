#ifndef PREFLIB_DISASSEMBLER_DISASSEMBLERENGINE_H
#define PREFLIB_DISASSEMBLER_DISASSEMBLERENGINE_H

#include <deque>
#include "../core/lua/luax.h"
#include "../core/lua/luatable.h"
#include "disassemblerdefinition.h"
#include "disassemblerlisting.h"

namespace PrefLib {
namespace Disassembler {

class DisassemblerEngine: public LuaTable
{
    public:
        typedef void (*ProgressCallback)(const DataValue& address, void* param);

    public:
        DisassemblerEngine(DisassemblerDefinition* definition, lua_State* thread = nullptr);
        ~DisassemblerEngine();
        void setProgressCallback(ProgressCallback callback, void* param = nullptr);
        void disassemble(DisassemblerListing* listing);

    private:
        static bool sortBlocks(Block* b1, Block* b2);
        void prepareStack(DisassemblerListing* listing);

    lua_api:
        static int luaNext(lua_State* l);
        static int luaEnqueue(lua_State* l);

    private:
        DisassemblerDefinition* _definition;
        std::deque<DataValue> _queue;
        ProgressCallback _callback;
        void* _param;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_DISASSEMBLERENGINE_H
