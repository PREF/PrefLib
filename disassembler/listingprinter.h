#ifndef PREFLIB_DISASSEMBLER_LISTINGPRINTER_H
#define PREFLIB_DISASSEMBLER_LISTINGPRINTER_H

#include <utility>
#include <list>
#include "../core/luax.h"
#include "../core/luatable.h"
#include "../support/bytecolors.h"

namespace PrefLib {
namespace Disassembler {

using namespace Core;

class ListingPrinter: public LuaTable
{
    private:
        typedef std::pair<const char*, Support::ByteColors::Rgb> Chunk;

    public:
        ListingPrinter();
        ~ListingPrinter();
        void reset();

    lua_api:
        static int luaOut(lua_State* l);
        static int luaOutWord(lua_State* l);
        static int luaOutComment(lua_State* l);
        static int luaOutRegister(lua_State* l);
        static int luaOutValue(lua_State* l);

    private:
        std::list<ListingPrinter::Chunk> _chunks;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_LISTINGPRINTER_H
