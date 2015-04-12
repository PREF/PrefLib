#ifndef PREFLIB_DISASSEMBLER_LISTINGPRINTER_H
#define PREFLIB_DISASSEMBLER_LISTINGPRINTER_H

#include <utility>
#include <list>
#include "../core/lua/luax.h"
#include "../core/lua/luatable.h"
#include "../support/bytecolors.h"
#include "../types/datatype.h"
#include "../types/datavalue.h"

namespace PrefLib {
namespace Disassembler {

using namespace Core;

class ListingPrinter: public LuaTable
{
    public:
        typedef std::pair<const char*, Support::ByteColors::Rgb> Chunk;
        typedef std::list<ListingPrinter::Chunk> ChunkList;

    public:
        ListingPrinter();
        ~ListingPrinter();

    private:
        char* allocate(size_t len);

    public:
        ListingPrinter* out(const char* s);
        ListingPrinter* out(const char*, Support::ByteColors::Rgb rgb);
        ListingPrinter* outWord(const char* s);
        ListingPrinter* outWord(const char* s, Support::ByteColors::Rgb rgb);
        ListingPrinter* outComment(const char* s);
        ListingPrinter* outRegister(const char* s);
        ListingPrinter* outValue(lua_Integer value, DataType::Type datatype);
        ListingPrinter* outValue(lua_Integer value, DataType::Type datatype, lua_Integer base);
        virtual size_t length() const;
        const ChunkList& chunks() const;
        const char* toString();
        void reset();

    lua_api:
        static int luaOut(lua_State* l);
        static int luaOutWord(lua_State* l);
        static int luaOutComment(lua_State* l);
        static int luaOutRegister(lua_State* l);
        static int luaOutValue(lua_State* l);

    private:
        ChunkList _chunks;
        size_t _length;
        size_t _oldlength;
        char* _mergedstring;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_LISTINGPRINTER_H
