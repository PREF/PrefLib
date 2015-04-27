#ifndef PREFLIB_DISASSEMBLER_DISASSEMBLERLISTING_H
#define PREFLIB_DISASSEMBLER_DISASSEMBLERLISTING_H

#include <deque>
#include <capstone.h>
#include "../core/lua/luax.h"
#include "../core/lua/luatable.h"
#include "../core/lua/luacontainer.h"
#include "../io/databuffer.h"
#include "blocks/segment.h"
#include "blocks/function.h"
#include "blocks/instruction.h"
#include "blocks/capstoneinstruction.h"
#include "blocks/label.h"
#include "database/disassemblerdatabase.h"

namespace PrefLib {
namespace Disassembler {

using namespace Core;

class DisassemblerListing: public LuaTable
{
    public:
        class MemoryBuffer: public LuaTable
        {
            private:
                MemoryBuffer(DisassemblerListing* blocks, IO::DataBuffer* databuffer, lua_State* thread = nullptr);

            public:
                int read(uint64_t address, unsigned char* data, uint64_t len);

            lua_api:
                static int luaRead(lua_State* l);

            private:
                DisassemblerListing* _listing;
                IO::DataBuffer* _databuffer;

            friend class DisassemblerListing;
        };

    public:
        struct BlockInsertor
        {
            bool operator()(const LuaTable* t1, const LuaTable* t2)
            {
                const Block* b1 = dynamic_cast<const Block*>(t1);
                const Block* b2 = dynamic_cast<const Block*>(t2);

                if(b1->address() == b2->address())
                    throw std::runtime_error("Trying to insert blocks with the same address");

                return b1->endAddress() < b2->startAddress();
            }
        };

        struct AddressBlockComparator
        {
            bool operator()(uint64_t val, const LuaTable* t)
            {
                const Block* b = dynamic_cast<const Block*>(t);

                if(val > b->endAddress())
                    return 1;

                if(val < b->startAddress())
                    return -1;

                return 0;
            }
        };

        typedef std::deque<Block*> Listing;

    private:
        struct BlockContainer { LuaContainer ByIndex; LuaContainer ByAddress; };

    public:
        DisassemblerListing(IO::DataBuffer* databuffer, lua_State* thread = nullptr);
        ~DisassemblerListing();

    public:
        bool isDisassembled(DataValue& address);
        uint64_t baseAddress() const;
        MemoryBuffer* memoryBuffer() const;
        DisassemblerDatabase& database();
        IO::DataBuffer* dataBuffer() const;
        LuaContainer& segments();
        LuaContainer& functions();
        LuaContainer& entryPoints();
        LuaContainer& instructions();
        LuaContainer& bookmarks();
        const Listing& blocks();
        Instruction* findInstruction(uint64_t address);
        Function* findFunction(uint64_t address);
        Segment* findSegment(uint64_t address);
        Block* findBlock(uint64_t address);
        void createSegment(const char* name, Segment::Type segmenttype, uint64_t startaddress, uint64_t size, uint64_t offset);
        void createFunction(uint64_t address);
        void createFunction(const char* name, Function::Type functiontype, uint64_t address);
        void createEntryPoint(const char* name, uint64_t address);
        void createInstruction(Instruction* instruction);
        void createInstruction(CapstoneInstruction *csinstruction);
        void createLabel(uint64_t address, uint64_t sourceaddress);
        void createLabel(uint64_t address, uint64_t refaddress, const char* name);
        void createReference(uint64_t address, uint64_t referencedby);
        //void removeReference(uint64_t address, uint64_t referencedby);
        void createBookmark(Block* block, const char* description);
        void removeBookmark(Block* block);
        const char* getBookmark(Block* block);
        const LuaContainer* getReferences(Block* block);

    private:
        Block* guessBlock(uint64_t address);

    lua_api:
        static int luaCreateSegment(lua_State* l);
        static int luaCreateFunction(lua_State* l);
        static int luaCreateEntryPoint(lua_State* l);
        static int luaCreateInstruction(lua_State* l);
        static int luaCreateLabel(lua_State* l);
        static int luaCreateReference(lua_State* l);

    private:
        IO::DataBuffer* _databuffer;
        MemoryBuffer* _memorybuffer;
        DisassemblerDatabase _database;
        Listing _listing;
        LuaContainer _references;
        BlockContainer _bookmarks;
        BlockContainer _segments;
        BlockContainer _functions;
        BlockContainer _entrypoints;
        BlockContainer _instructions;
        BlockContainer _labels;

    friend class DisassemblerEngine;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_DISASSEMBLERLISTING_H
