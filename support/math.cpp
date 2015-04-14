#include "math.h"

namespace PrefLib {
namespace Support {

Math::Math()
{

}

Math::~Math()
{

}

void Math::pushTable(lua_State* l)
{
    lua_newtable(l);

    lua_pushcfunction(l, &Math::luaLogn);
    lua_setfield(l, -2, "logn");

    lua_pushcfunction(l, &Math::luaEntropy);
    lua_setfield(l, -2, "entropy");
}

double Math::logn(double n, unsigned int base)
{
    return log(n) / log(base);
}

double Math::entropy(const ByteElaborator::CountResult& cr, uint64_t size)
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

double Math::entropy(IO::DataBuffer *databuffer, uint64_t startoffset, uint64_t size, volatile bool *cancontinue)
{
    ByteElaborator::CountResult cr;
    ByteElaborator::countBytes(cr, databuffer, startoffset, startoffset + size, cancontinue);
    return Math::entropy(cr, size);
}

double Math::entropy(IO::DataBuffer *databuffer, uint64_t size, volatile bool *cancontinue)
{
    return Math::entropy(databuffer, 0, size, cancontinue);
}

double Math::entropy(IO::DataBuffer *databuffer, volatile bool *cancontinue)
{
    return Math::entropy(databuffer, databuffer->length(), cancontinue);
}

int Math::luaLogn(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 2);

    lua_pushnumber(l, Math::logn(luaL_checknumber(l, 1), luaL_checknumber(l, 2)));
    return 1;
}

int Math::luaEntropy(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectminargc(l, argc, 1);

    IO::DataBuffer* databuffer = reinterpret_cast<IO::DataBuffer*>(LuaTable::checkThis(l, 1));
    lua_pushnumber(l, Math::entropy(databuffer, luaL_optinteger(l, 2, 0), luaL_optinteger(l, 3, databuffer->length())));
    return 1;
}

} // namespace Support
} // namespace PrefLib

