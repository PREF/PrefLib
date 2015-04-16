#include "listingprinter.h"

namespace PrefLib {
namespace Disassembler {

ListingPrinter::ListingPrinter(lua_State *thread): LuaTable(thread), _length(0), _oldlength(0), _mergedstring(nullptr)
{
    this->setFunction("out", &ListingPrinter::luaOut);
    this->setFunction("outword", &ListingPrinter::luaOutWord);
    this->setFunction("outcomment", &ListingPrinter::luaOutComment);
    this->setFunction("outregister", &ListingPrinter::luaOutRegister);
    this->setFunction("outvalue", &ListingPrinter::luaOutValue);
}

ListingPrinter::~ListingPrinter()
{
    this->reset();
}

char *ListingPrinter::allocate(size_t len)
{
    char* s = new char[len + 1];
    s[len] = '\0';

    this->_length += len;
    return s;
}

ListingPrinter *ListingPrinter::out(const char *s)
{
    return this->out(s, 0x000000);
}

ListingPrinter *ListingPrinter::out(const char* s, Support::ByteColors::Rgb rgb)
{
    this->_chunks.push_back(Chunk(strdup(s), rgb));
    this->_length += strlen(s);
    return this;
}

ListingPrinter *ListingPrinter::outWord(const char *s)
{
    return this->outWord(s, 0x000000);
}

ListingPrinter *ListingPrinter::outWord(const char *s, Support::ByteColors::Rgb rgb)
{
    size_t len = strlen(s) + 1;
    char* res = this->allocate(len);
    snprintf(res, len + 1, "%s ", s);

    this->_chunks.push_back(Chunk(res, rgb));
    return this;
}

ListingPrinter *ListingPrinter::outComment(const char *s)
{
    size_t len = strlen(s) + 3;
    char* res = this->allocate(len);
    snprintf(res, len + 1, "\t# %s", s);

    this->_chunks.push_back(Chunk(res, 0x800000));
    return this;
}

ListingPrinter *ListingPrinter::outRegister(const char *s)
{
    size_t len = strlen(s) + 1;
    char* res = this->allocate(len);
    snprintf(res, len + 1, "$%s", s);

    this->_chunks.push_back(Chunk(res, 0x800000));
    return this;
}

ListingPrinter *ListingPrinter::outValue(lua_Integer value, DataType::Type datatype)
{
    return this->outValue(value, datatype, 16);
}

ListingPrinter *ListingPrinter::outValue(lua_Integer value, DataType::Type datatype, lua_Integer base)
{
    size_t w = DataType::sizeOf(datatype) * 2;

    DataValue dv = value; /* Use DataValue in order to avoid duplicate code */
    dv.castTo(datatype);

    const char* s = dv.toString(base, w);
    this->_chunks.push_back(Chunk(strdup(s), 0x000080));
    this->_length += strlen(s);
    return this;
}

size_t ListingPrinter::length() const
{
    return this->_length;
}

const ListingPrinter::ChunkList &ListingPrinter::chunks() const
{
    return this->_chunks;
}

const char *ListingPrinter::toString()
{
    if((this->_oldlength != this->_length) || !this->_mergedstring) // Check if the string is changed/not created
    {
        this->_oldlength = this->_length;

        if(this->_mergedstring)
            delete[] this->_mergedstring;

        this->_mergedstring = new char[this->_length + 1];
        this->_mergedstring[this->_length] = '\0';

        ChunkList::iterator it = this->_chunks.begin();

        for(size_t offset = 0u; it != this->_chunks.end(); it++)
        {
            const char* s = (*it).first;
            strcpy(this->_mergedstring + offset, s);
            offset += strlen(s);
        }
    }

    return this->_mergedstring;
}

void ListingPrinter::reset()
{
    ChunkList::iterator it = this->_chunks.begin();

    for(; it != this->_chunks.end(); it++)
        delete[] (*it).first;

    this->_chunks.clear();
    this->_length = 0;
    this->_oldlength = 0;

    if(this->_mergedstring)
    {
        delete[] this->_mergedstring;
        this->_mergedstring = nullptr;
    }
}

int ListingPrinter::luaOut(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectminargc(l, argc, 2);

    ListingPrinter* thethis = reinterpret_cast<ListingPrinter*>(checkThis(l, 1));

    thethis->out(luaL_checkstring(l, 2), static_cast<Support::ByteColors::Rgb>(luaL_optinteger(l, 3, 0x000000)));
    thethis->push(); /* For Chaining */
    return 1;
}

int ListingPrinter::luaOutWord(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectminargc(l, argc, 2);

    ListingPrinter* thethis = reinterpret_cast<ListingPrinter*>(checkThis(l, 1));

    thethis->outWord(luaL_checkstring(l, 2), static_cast<Support::ByteColors::Rgb>(luaL_optinteger(l, 3, 0x000000)));
    thethis->push(); /* For Chaining */
    return 1;
}

int ListingPrinter::luaOutComment(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 2);

    ListingPrinter* thethis = reinterpret_cast<ListingPrinter*>(checkThis(l, 1));

    thethis->outComment(luaL_checkstring(l, 2));
    thethis->push(); /* For Chaining */
    return 1;
}

int ListingPrinter::luaOutRegister(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 2);

    ListingPrinter* thethis = reinterpret_cast<ListingPrinter*>(checkThis(l, 1));

    thethis->outRegister(luaL_checkstring(l, 2));
    thethis->push(); /* For Chaining */
    return 1;
}

int ListingPrinter::luaOutValue(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectminargc(l, argc, 3);

    ListingPrinter* thethis = reinterpret_cast<ListingPrinter*>(checkThis(l, 1));

    thethis->outValue(luaL_checkinteger(l, 2), static_cast<DataType::Type>(luaL_checkinteger(l, 3)), luaL_optinteger(l, 4, 16));
    thethis->push(); /* For Chaining */
    return 1;
}

} // namespace Disassembler
} // namespace PrefLib

