#include "disassemblerdefinition.h"

namespace PrefLib {
namespace Disassembler {

DisassemblerDefinition::DisassemblerDefinition(const char* name, Format::FormatDefinition* formatdefinition, DataType::Type addresstype, const char* author, const char* version): LuaTable()
{
    this->setString("name", name);
    this->setTable("format", formatdefinition);
    this->setInteger("addresstype", addresstype);
    this->setString("author", author);
    this->setString("version", version);
}

DisassemblerDefinition::~DisassemblerDefinition()
{

}

void DisassemblerDefinition::initialize()
{
    if(!this->hasField("initialize"))
        return;

    lua_State* l = LuaState::instance();

    this->push();
    lua_getfield(l, -1, "initialize");
    this->push(); // Self
    this->protectedCall(1, 0);
    lua_pop(l, 1);
}

void DisassemblerDefinition::finalize()
{
    if(!this->hasField("finalize"))
        return;

    lua_State* l = LuaState::instance();

    this->push();
    lua_getfield(l, -1, "finalize");
    this->push(); // Self
    this->protectedCall(1, 0);
    lua_pop(l, 1);
}

void DisassemblerDefinition::map(DisassemblerListing *listing)
{
    if(!this->hasField("map"))
        return;

    Format::FormatTree* formattree = this->format()->build(listing->dataBuffer());
    listing->setTable("formattree", formattree);

    lua_State* l = LuaState::instance();

    this->push();
    lua_getfield(l, -1, "map");
    this->push(); // Self
    listing->push();
    this->protectedCall(2, 0);
    lua_pop(l, 1);
}

lua_Integer DisassemblerDefinition::disassemble(LuaTable *engine, DisassemblerListing* listing, const DataValue &address)
{
    if(!this->hasField("disassemble"))
        return 0;

    lua_State* l = LuaState::instance();

    this->push();
    lua_getfield(l, -1, "disassemble");
    this->push(); // Self
    engine->push();
    listing->push();
    address.push();
    this->protectedCall(4, 1);

    lua_Integer res = luaL_checkinteger(l, -1);
    lua_pop(l, 2);
    return res;
}

void DisassemblerDefinition::output(ListingPrinter *printer, Instruction *instruction)
{
    if(!this->hasField("output"))
        return;

    lua_State* l = LuaState::instance();
    printer->reset();

    this->push();
    lua_getfield(l, -1, "output");
    this->push(); // Self
    printer->push();
    instruction->push();
    this->protectedCall(3, 0);
    lua_pop(l, 1);
}

const char* DisassemblerDefinition::name() const
{
    return this->getString("name");
}

const char* DisassemblerDefinition::author() const
{
    return this->getString("author");
}

const char* DisassemblerDefinition::version() const
{
    return this->getString("version");
}

const Format::FormatDefinition *DisassemblerDefinition::format() const
{
    return dynamic_cast<Format::FormatDefinition*>(this->getTable("format"));
}

DataType::Type DisassemblerDefinition::addressType() const
{
    return static_cast<DataType::Type>(this->getInteger("addresstype"));
}

} // namespace Disassembler
} // namespace PrefLib

