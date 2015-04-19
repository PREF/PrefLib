#include "algorithm.h"

namespace PrefLib {
namespace Support {

Algorithm::Algorithm()
{

}

Algorithm::~Algorithm()
{

}

void Algorithm::push(lua_State *l)
{
    lua_newtable(l);

    lua_pushcfunction(l, &Algorithm::luaEntropy);
    lua_setfield(l, -2, "entropy");

    lua_pushcfunction(l, &Algorithm::luaRebase);
    lua_setfield(l, -2, "rebase");

    lua_pushcfunction(l, &Algorithm::luaPointer);
    lua_setfield(l, -2, "pointer");
}

uint64_t Algorithm::rebase(uint64_t address, uint64_t oldbaseaddress, uint64_t newbaseaddress)
{
    return (address - oldbaseaddress) + newbaseaddress;
}

double Algorithm::entropy(const ByteElaborator::CountResult& cr, uint64_t size)
{
    double e = 0.0;
    uint64_t base = std::min(size, 256ul);

    for(uint64_t i = 0; i < cr.Counts.size(); i++)
    {
        const uintmax_t& c = cr.Counts.at(i);

        if(!c)
            continue;

        double freq = static_cast<double>(c) / static_cast<double>(size);
        e += freq * Math::logn(freq, base);
    }

    return -e;
}

double Algorithm::entropy(IO::DataBuffer *databuffer, uint64_t startoffset, uint64_t size, volatile bool *cancontinue)
{
    ByteElaborator::CountResult cr;
    ByteElaborator::countBytes(cr, databuffer, startoffset, startoffset + size, cancontinue);
    return Algorithm::entropy(cr, size);
}

double Algorithm::entropy(IO::DataBuffer *databuffer, uint64_t size, volatile bool *cancontinue)
{
    return Algorithm::entropy(databuffer, 0, size, cancontinue);
}

double Algorithm::entropy(IO::DataBuffer *databuffer, volatile bool *cancontinue)
{
    return Algorithm::entropy(databuffer, databuffer->length(), cancontinue);
}

int Algorithm::luaEntropy(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectminargc(l, argc, 1);

    IO::DataBuffer* databuffer = reinterpret_cast<IO::DataBuffer*>(LuaTable::checkThis(l, 1));
    lua_pushnumber(l, Algorithm::entropy(databuffer, luaL_optinteger(l, 2, 0), luaL_optinteger(l, 3, databuffer->length())));
    return 1;
}

int Algorithm::luaRebase(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectminargc(l, argc, 3);

    lua_pushinteger(l, Algorithm::rebase(luaL_checkinteger(l, 1), luaL_checkinteger(l, 2), luaL_checkinteger(l, 3)));
    return 1;
}

int Algorithm::luaPointer(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectminargc(l, argc, 3);

    Pointer pointer(luaL_checkinteger(l, 1), static_cast<DataType::Type>(luaL_checkinteger(l, 2)), reinterpret_cast<IO::DataBuffer*>(LuaTable::checkThis(l, 3)), l);
    pointer.push();
    return 1;
}

} // namespace Support
} // namespace PrefLib

