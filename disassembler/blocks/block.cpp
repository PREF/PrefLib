#include "block.h"

namespace PrefLib {
namespace Disassembler {

Block::Block(uint64_t startaddress, uint64_t size, lua_State *thread): LuaTable(thread), _bookmarked(false)
{
    lua_State* l = LuaState::instance();

    this->setInteger("startaddress", startaddress);
    this->setInteger("size", size);

    this->push();

    if(luaL_newmetatable(l, "block"))
    {
        lua_pushcfunction(l, &Block::luaMetaIndex);
        lua_setfield(l, -2, "__index");

        lua_pushcfunction(l, &Block::luaMetaNewIndex);
        lua_setfield(l, -2, "__newindex");
    }

    lua_setmetatable(l, -2);
    lua_pop(l, 1);
}

Block::~Block()
{

}

bool Block::isInstructionBlock() const
{
    return this->type() == Type::InstructionBlock;
}

bool Block::isFunctionBlock() const
{
    return this->type() == Type::FunctionBlock;
}

bool Block::isSegmentBlock() const
{
    return this->type() == Type::SegmentBlock;
}

bool Block::isLabelBlock() const
{
    return this->type() == Type::LabelBlock;
}

bool Block::isEmpty() const
{
    return this->size() == 0;
}

bool Block::isCommented() const
{
    return this->hasField("comment");
}

bool Block::isBookmarked() const
{
    return this->_bookmarked;
}

bool Block::contains(uint64_t address)
{
    return (address >= this->startAddress()) && (address < this->endAddress());
}

uint64_t Block::address() const
{
    return this->startAddress();
}

uint64_t Block::startAddress() const
{
    return this->getInteger("startaddress");
}

uint64_t Block::endAddress() const
{
    return this->startAddress() + this->size();
}

uint64_t Block::size() const
{
    return this->getInteger("size");
}

uint8_t Block::weight() const
{
    return this->type();
}

const char *Block::comment() const
{
    return this->getString("comment");
}

void Block::setBookmarked(bool b)
{
    this->_bookmarked = b;
}

void Block::setComment(const char *s)
{
    this->setString("comment", s);
}

int Block::metaIndex(lua_State *l)
{
    const char* arg = luaL_checkstring(l, 2);

    if(!strcmp(arg, "address")) /* Syntactic sugar */
    {
        lua_pushinteger(l, this->address());
        return 1;
    }

    if(!strcmp(arg, "endaddress"))
    {
        lua_pushinteger(l, this->endAddress());
        return 1;
    }

    return 0;
}

int Block::metaNewIndex(lua_State *l)
{
    (void)l; // Unused Parameter;

    return 0;
}

int Block::luaMetaIndex(lua_State *l)
{
    Block* thethis = reinterpret_cast<Block*>(checkThis(l, 1));
    return thethis->metaIndex(l);
}

int Block::luaMetaNewIndex(lua_State *l)
{
    Block* thethis = reinterpret_cast<Block*>(checkThis(l, 1));
    return thethis->metaNewIndex(l);
}

} // namespace Disassembler
} // namespace PrefLib

