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
    this->setFunction("createSegment", &DisassemblerListing::luaCreateSegment);
    this->setFunction("createFunction", &DisassemblerListing::luaCreateFunction);
    this->setFunction("createEntryPoint", &DisassemblerListing::luaCreateEntryPoint);
    this->setFunction("createInstruction", &DisassemblerListing::luaCreateInstruction);
    this->setFunction("createLabel", &DisassemblerListing::luaCreateLabel);
    this->setFunction("createReference", &DisassemblerListing::luaCreateReference);
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

LuaContainer &DisassemblerListing::bookmarks()
{
    return this->_bookmarks.ByIndex;
}

const DisassemblerListing::Listing &DisassemblerListing::blocks()
{
    return this->_listing;
}

Instruction *DisassemblerListing::findInstruction(uint64_t address)
{    
    if(this->_instructions.ByAddress.hasField(address))
        return dynamic_cast<Instruction*>(this->_instructions.ByAddress.getI<LuaTable*>(address));

    lua_Integer idx = this->_instructions.ByIndex.binarySearch<uint64_t, LuaTable*, DisassemblerListing::AddressBlockComparator>(address);

    if(idx == -1)
        return nullptr;

    return dynamic_cast<Instruction*>(this->_instructions.ByIndex.getI<LuaTable*>(idx));
}

Function *DisassemblerListing::findFunction(uint64_t address)
{
    if(this->_functions.ByAddress.hasField(address))
        return dynamic_cast<Function*>(this->_functions.ByAddress.getI<LuaTable*>(address));

    lua_Integer idx = this->_functions.ByIndex.binarySearch<uint64_t, LuaTable*, DisassemblerListing::AddressBlockComparator>(address);

    if(idx == -1)
        return nullptr;

    return dynamic_cast<Function*>(this->_functions.ByIndex.getI<LuaTable*>(idx));
}

Segment *DisassemblerListing::findSegment(uint64_t address)
{
    if(this->_segments.ByAddress.hasField(address))
        return dynamic_cast<Segment*>(this->_functions.ByAddress.getI<LuaTable*>(address));

    lua_Integer idx = this->_segments.ByIndex.binarySearch<uint64_t, LuaTable*, DisassemblerListing::AddressBlockComparator>(address);

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

void DisassemblerListing::createFunction(uint64_t address)
{
    this->createFunction(nullptr, Function::FunctionBlock, address);
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

    if(!name)
    {
        size_t sz = sizeof(uint64_t) + 4; // +4: "sub_"
        char* s = new char[sz + 1];

        s[sz] = '\0';
        snprintf(s, sz + 1, "sub_%" PRIX64, address);

        this->_database.set(address, s);
        delete[] s;
    }
    else
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

void DisassemblerListing::createReference(uint64_t address, uint64_t referencedby)
{
    Block* destinationblock = this->guessBlock(address);
    Block* referenceblock = dynamic_cast<Block*>(static_cast<LuaTable*>(this->_instructions.ByAddress[referencedby]));

    if(!destinationblock)
        return;

    LuaContainer* references = nullptr;
    destinationblock->setReferenced(true);

    if(!this->_references.hasField(address))
    {
        references = new LuaContainer();
        this->_references[address] = references;
    }
    else
        references = dynamic_cast<LuaContainer*>(static_cast<LuaTable*>(this->_references[address])); // TODO: Improvement Needed

    references->binaryInsert<LuaTable*, DisassemblerListing::BlockInsertor>(referenceblock);
}

/*
void DisassemblerListing::removeReference(uint64_t address, uint64_t referencedby)
{
    if(!this->_references.hasField(address))
        return;

    // TODO: Improvement Needed
    LuaContainer* references = dynamic_cast<LuaContainer*>(static_cast<LuaTable*>(this->_references[address]));
    int idx = references->binarySearch<uint64_t, LuaTable*, DisassemblerListing::AddressBlockComparator>(referencedby);

    if(idx == -1)
        return;

    references->remove(idx);

    if(references->isEmpty())
    {
        Block* referenceblock = dynamic_cast<Block*>(static_cast<LuaTable*>(this->_instructions.ByAddress[referencedby]));
        referenceblock->setReferenced(false);

        this->_references.removeKey(address);
        delete references;
    }
}
*/

void DisassemblerListing::createLabel(uint64_t address, uint64_t sourceaddress)
{
    this->createLabel(address, sourceaddress, nullptr);
}

void DisassemblerListing::createLabel(uint64_t address, uint64_t referencedby, const char *name)
{
    Label* label = nullptr;

    if(!this->_labels.ByAddress.hasField(address))
    {
        label = new Label(address);

        this->_labels.ByIndex.binaryInsert<LuaTable*, DisassemblerListing::BlockInsertor>(label);
        this->_labels.ByAddress[label->address()] = label;
        this->_listing.push_back(label);
    }
    else
        label = dynamic_cast<Label*>(static_cast<LuaTable*>(this->_labels.ByAddress[address])); //TODO: Improvement Needed

    this->_database.set(address, name);
    this->createReference(address, referencedby);
}

void DisassemblerListing::createBookmark(Block *block, const char *description)
{
    block->setBookmarked(true);

    this->_bookmarks.ByIndex.append(block);
    this->_bookmarks.ByAddress[block->address()] = description;
}

void DisassemblerListing::removeBookmark(Block *block)
{
    block->setBookmarked(false);

    for(size_t i = 0; i < this->_bookmarks.ByIndex.length(); i++)
    {
        if(block == this->_bookmarks.ByIndex.getI<LuaTable*>(i))
        {
            this->_bookmarks.ByIndex.remove(i);
            break;
        }
    }

    this->_bookmarks.ByAddress.removeKey(block->address());
}

const char *DisassemblerListing::getBookmark(const Block *block)
{
    if(!block->isBookmarked())
        return nullptr;

    return this->_bookmarks.ByAddress[block->address()];
}

const LuaContainer *DisassemblerListing::getReferences(const Block *block)
{
    if(!block->isRerefenced())
        return nullptr;

    //TODO: Improvement Needed
    return dynamic_cast<const LuaContainer*>(static_cast<LuaTable*>(this->_references[block->address()]));
}

Block *DisassemblerListing::guessBlock(uint64_t address)
{
    if(this->_segments.ByAddress.hasField(address)) // Is Start of Segment?
        return dynamic_cast<Block*>(static_cast<LuaTable*>(this->_segments.ByAddress[address]));
    else if(this->_functions.ByAddress.hasField(address))  // Is Start of Function?
        return dynamic_cast<Block*>(static_cast<LuaTable*>(this->_functions.ByAddress[address]));
    else if(this->_labels.ByAddress.hasField(address))  // Is a Label (Jump/Call)
        return dynamic_cast<Block*>(static_cast<LuaTable*>(this->_labels.ByAddress[address]));
    else if(this->_instructions.ByAddress.hasField(address))  // Is an Instruction?
        return dynamic_cast<Block*>(static_cast<LuaTable*>(this->_instructions.ByAddress[address]));

    return nullptr; // Is nothing known
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

int DisassemblerListing::luaCreateLabel(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectminargc(l, argc, 3);

    DisassemblerListing* thethis = reinterpret_cast<DisassemblerListing*>(checkThis(l, 1));
    thethis->createLabel(luaL_checkinteger(l, 2), luaL_checkinteger(l, 3), luaL_optstring(l, 4, nullptr));
    return 0;
}

int DisassemblerListing::luaCreateReference(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 3);

    DisassemblerListing* thethis = reinterpret_cast<DisassemblerListing*>(checkThis(l, 1));
    thethis->createReference(luaL_checkinteger(l, 2), luaL_checkinteger(l, 3));
    return 0;
}

} // namespace Disassembler
} // namespace PrefLib

