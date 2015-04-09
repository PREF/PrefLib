#ifndef PREFLIB_DISASSEMBLER_DISASSEMBLERLISTING_H
#define PREFLIB_DISASSEMBLER_DISASSEMBLERLISTING_H

#include <capstone.h>
#include "../core/luax.h"
#include "../core/luatable.h"
#include "../core/luacontainer.h"
#include "../io/databuffer.h"
#include "blocks/segment.h"
#include "blocks/function.h"
#include "blocks/instruction.h"
#include "blocks/capstoneinstruction.h"

namespace PrefLib {
namespace Disassembler {

using namespace Core;

class DisassemblerListing: public LuaTable
{
    public:
        class MemoryBuffer: public LuaTable
        {
            private:
                MemoryBuffer(DisassemblerListing* listing, IO::DataBuffer* databuffer);

            public:
                int read(uint64_t address, unsigned char* data, uint64_t len);

            lua_api:
                static int luaRead(lua_State* l);

            private:
                DisassemblerListing* _listing;
                IO::DataBuffer* _databuffer;

            friend class DisassemblerListing;
        };

    private:
        struct BlockContainer { LuaContainer ByIndex; LuaContainer ByAddress; };

    public:
        DisassemblerListing(IO::DataBuffer* databuffer);
        ~DisassemblerListing();

    public:
        bool isDisassembled(DataValue& address);
        uint64_t baseAddress() const;
        MemoryBuffer* memoryBuffer() const;
        IO::DataBuffer* dataBuffer() const;
        LuaContainer& segments();
        LuaContainer& functions();
        LuaContainer& entryPoints();
        LuaContainer& instructions();
        Segment* findSegment(uint64_t address);
        void createSegment(const char* name, Segment::Type segmenttype, uint64_t startaddress, uint64_t size, uint64_t offset);
        void createFunction(const char* name, Function::Type functiontype, uint64_t address);
        void createEntryPoint(const char* name, uint64_t address);
        void addInstruction(Instruction* instruction);
        void addInstruction(csh handle, cs_insn* insn);

    lua_api:
        static int luaCreateSegment(lua_State* l);
        static int luaCreateFunction(lua_State* l);
        static int luaCreateEntryPoint(lua_State* l);
        static int luaAddInstruction(lua_State* l);

    private:
        IO::DataBuffer* _databuffer;
        MemoryBuffer* _memorybuffer;
        BlockContainer _segments;
        BlockContainer _functions;
        BlockContainer _entrypoints;
        BlockContainer _instructions;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_DISASSEMBLERLISTING_H
