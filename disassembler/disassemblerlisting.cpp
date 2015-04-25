#include "disassemblerlisting.h"

namespace PrefLib {
namespace Disassembler {

DisassemblerListing::MemoryBuffer::MemoryBuffer(DisassemblerListing *listing, IO::DataBuffer *databuffer, lua_State *thread): LuaTable(thread), _listing(listing), _databuffer(databuffer)
{    
    this->setFunction("read", &MemoryBuffer::luaRead);
}

int DisassemblerListing::MemoryBuffer::read(uint64_t address, unsigned char *data, uint64_t len)
{
    Segment* segment = this->_listing->findSegment(address);

    if(!segment)
        return 0;

    uint64_t offset = segment->calculateOffset(address);
    return this->_databuffer->read(offset, data, len);
}

int DisassemblerListing::MemoryBuffer::luaRead(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 3);

    MemoryBuffer* thethis = reinterpret_cast<MemoryBuffer*>(checkThis(l, 1));
    uint64_t address = luaL_checkinteger(l, 2);
    uint64_t len = luaL_checkinteger(l, 3);

    Buffer buffer(len);
    thethis->read(address, &buffer, len);
    buffer.push();
    return 1;
}

DisassemblerListing::DisassemblerListing(IO::DataBuffer *databuffer, lua_State *thread): LuaTable(thread), _databuffer(databuffer)
{
    this->_memorybuffer = new MemoryBuffer(this, databuffer);

    this->push();
    this->setInteger("baseaddress", 0);
    this->setTable("memorybuffer", this->_memorybuffer);
    this->setTable("segments", &this->_segments.ByIndex);
    this->setTable("segmentmap", &this->_segments.ByAddress);
    this->setTable("functions", &this->_functions.ByIndex);
    this->setTable("functionmap", &this->_functions.ByAddress);
    this->setTable("entrypoints", &this->_entrypoints.ByIndex);
    this->setTable("entrypointmap", &this->_entrypoints.ByAddress);
    this->setFunction("createsegment", &DisassemblerListing::luaCreateSegment);
    this->setFunction("createfunction", &DisassemblerListing::luaCreateFunction);
    this->setFunction("createentrypoint", &DisassemblerListing::luaCreateEntryPoint);
    this->setFunction("createinstruction", &DisassemblerListing::luaCreateInstruction);
    lua_pop(this->_thread, 1);
}

DisassemblerListing::~DisassemblerListing()
{
    if(this->_memorybuffer)
    {
        delete this->_memorybuffer;
        this->_memorybuffer = nullptr;
    }
}

bool DisassemblerListing::isDisassembled(DataValue& address)
{
    return this->_instructions.ByAddress.hasField(static_cast<uint64_t>(address));
}

uint64_t DisassemblerListing::baseAddress() const
{
    return static_cast<uint64_t>(this->getInteger("baseaddress"));
}

DisassemblerListing::MemoryBuffer *DisassemblerListing::memoryBuffer() const
{
    return this->_memorybuffer;
}

DisassemblerDatabase& DisassemblerListing::database()
{
    return this->_database;
}

IO::DataBuffer *DisassemblerListing::dataBuffer() const
{
    return this->_databuffer;
}

LuaContainer& DisassemblerListing::segments()
{
    return this->_segments.ByIndex;
}

LuaContainer &DisassemblerListing::functions()
{
    return this->_functions.ByIndex;
}

LuaContainer &DisassemblerListing::entryPoints()
{
    return this->_entrypoints.ByIndex;
}

LuaContainer &DisassemblerListing::instructions()
{
    return this->_instructions.ByIndex;
}

const DisassemblerListing::Listing &DisassemblerListing::blocks()
{
    return this->_listing;
}

Instruction *DisassemblerListing::findInstruction(uint64_t address)
{    
    if(this->_instructions.ByAddress.hasField(address))
        return dynamic_cast<Instruction*>(this->_instructions.ByAddress.getI<LuaTable*>(address));

    lua_Integer idx = this->_instructions.ByIndex.binarySearch<uint64_t, LuaTable*, DisassemblerListing::BlockComparator>(address);

    if(idx == -1)
        return nullptr;

    return dynamic_cast<Instruction*>(this->_instructions.ByIndex.getI<LuaTable*>(idx));
}

Function *DisassemblerListing::findFunction(uint64_t address)
{
    if(this->_functions.ByAddress.hasField(address))
        return dynamic_cast<Function*>(this->_functions.ByAddress.getI<LuaTable*>(address));

    lua_Integer idx = this->_functions.ByIndex.binarySearch<uint64_t, LuaTable*, DisassemblerListing::BlockComparator>(address);

    if(idx == -1)
        return nullptr;

    return dynamic_cast<Function*>(this->_functions.ByIndex.getI<LuaTable*>(idx));
}

Segment *DisassemblerListing::findSegment(uint64_t address)
{
    if(this->_segments.ByAddress.hasField(address))
        return dynamic_cast<Segment*>(this->_functions.ByAddress.getI<LuaTable*>(address));

    lua_Integer idx = this->_segments.ByIndex.binarySearch<uint64_t, LuaTable*, DisassemblerListing::BlockComparator>(address);

    if(idx == -1)
        return nullptr;

    return dynamic_cast<Segment*>(this->_segments.ByIndex.getI<LuaTable*>(idx));
}

Block *DisassemblerListing::findBlock(uint64_t address)
{
    Block* block = nullptr;

    block = this->findInstruction(address);

    if(block)
        return block;

    block = this->findFunction(address);

    if(block)
        return block;

    return this->findSegment(address);
}

void DisassemblerListing::createSegment(const char *name, Segment::Type segmenttype, uint64_t startaddress, uint64_t size, uint64_t baseoffset)
{
    Segment* segment = new Segment(name, segmenttype, startaddress, size, baseoffset);

    this->_segments.ByIndex.binaryInsert<LuaTable*, DisassemblerListing::BlockInsertor>(segment);
    this->_segments.ByAddress[startaddress] = segment;

    this->_listing.push_back(segment);
}

void DisassemblerListing::createFunction(const char *name, Function::Type functiontype, uint64_t address)
{
    Function* function = new Function(functiontype, address);

    this->_functions.ByIndex.binaryInsert<LuaTable*, DisassemblerListing::BlockInsertor>(function);
    this->_functions.ByAddress[address] = function;

    if(functiontype & Function::EntryPointBlock)
    {
        this->_entrypoints.ByIndex.binaryInsert<LuaTable*, DisassemblerListing::BlockInsertor>(function);
        this->_entrypoints.ByAddress[address] = function;
    }

    this->_database.set(address, name);
    this->_listing.push_back(function);
}

void DisassemblerListing::createEntryPoint(const char *name, uint64_t address)
{
    this->createFunction(name, Function::EntryPointBlock, address);
}

void DisassemblerListing::createInstruction(Instruction *instruction)
{
    this->_instructions.ByIndex.binaryInsert<LuaTable*, DisassemblerListing::BlockInsertor>(instruction);
    this->_instructions.ByAddress[instruction->address()] = instruction;
    this->_listing.push_back(instruction);
}

void DisassemblerListing::createInstruction(CapstoneInstruction* csinstruction)
{
    this->_instructions.ByIndex.binaryInsert<LuaTable*, DisassemblerListing::BlockInsertor>(csinstruction);
    this->_instructions.ByAddress[csinstruction->address()] = csinstruction;
    this->_listing.push_back(csinstruction);
}

int DisassemblerListing::luaCreateSegment(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 6);

    DisassemblerListing* thethis = reinterpret_cast<DisassemblerListing*>(checkThis(l, 1));
    thethis->createSegment(luaL_checkstring(l, 2), static_cast<Segment::Type>(luaL_checkinteger(l, 3)), luaL_checkinteger(l, 4), luaL_checkinteger(l, 5), luaL_checkinteger(l, 6));
    return 0;
}

int DisassemblerListing::luaCreateFunction(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 4);

    DisassemblerListing* thethis = reinterpret_cast<DisassemblerListing*>(checkThis(l, 1));
    thethis->createFunction(luaL_checkstring(l, 2), static_cast<Function::Type>(luaL_checkinteger(l, 3)), luaL_checkinteger(l, 4));
    return 0;
}

int DisassemblerListing::luaCreateEntryPoint(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 3);

    DisassemblerListing* thethis = reinterpret_cast<DisassemblerListing*>(checkThis(l, 1));
    thethis->createEntryPoint(luaL_checkstring(l, 2), luaL_checkinteger(l, 3));
    return 0;
}

int DisassemblerListing::luaCreateInstruction(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectminargc(l, argc, 2);

    DisassemblerListing* thethis = reinterpret_cast<DisassemblerListing*>(checkThis(l, 1));

    if(argc == 3) /* Capstone Instruction */
    {
        lua_pushvalue(l, 3);
        int ref = luaL_ref(l, LUA_REGISTRYINDEX);

        CapstoneInstruction* csinstruction = new CapstoneInstruction(static_cast<csh>(luaL_checkinteger(l, 2)), *(reinterpret_cast<cs_insn**>(luaL_checkudata(l, 3, "cs_insn"))), ref);
        thethis->createInstruction(csinstruction);
        return 0;
    }

    thethis->createInstruction(reinterpret_cast<Instruction*>(checkThis(l, 3)));
    return 0;
}

} // namespace Disassembler
} // namespace PrefLib

