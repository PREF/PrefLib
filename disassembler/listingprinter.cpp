#include "listingprinter.h"

namespace PrefLib {
namespace Disassembler {

ListingPrinter::ListingPrinter()
{

}

ListingPrinter::~ListingPrinter()
{

}

void ListingPrinter::reset()
{
    this->_chunks.clear();
}

int ListingPrinter::luaOut(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    ListingPrinter* thethis = reinterpret_cast<ListingPrinter*>(checkThis(l, 1));

    thethis->push(); /* For Chaining */
    return 1;
}

int ListingPrinter::luaOutWord(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    ListingPrinter* thethis = reinterpret_cast<ListingPrinter*>(checkThis(l, 1));

    thethis->push(); /* For Chaining */
    return 1;
}

int ListingPrinter::luaOutComment(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    ListingPrinter* thethis = reinterpret_cast<ListingPrinter*>(checkThis(l, 1));

    thethis->push(); /* For Chaining */
    return 1;
}

int ListingPrinter::luaOutRegister(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    ListingPrinter* thethis = reinterpret_cast<ListingPrinter*>(checkThis(l, 1));

    thethis->push(); /* For Chaining */
    return 1;
}

int ListingPrinter::luaOutValue(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    ListingPrinter* thethis = reinterpret_cast<ListingPrinter*>(checkThis(l, 1));

    thethis->push(); /* For Chaining */
    return 1;
}

} // namespace Disassembler
} // namespace PrefLib

