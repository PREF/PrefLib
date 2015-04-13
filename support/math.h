#ifndef PREFLIB_SUPPORT_MATH_H
#define PREFLIB_SUPPORT_MATH_H

#include <cmath>
#include "core/lua/luatable.h"
#include "io/databuffer.h"
#include "byteelaborator.h"

namespace PrefLib {
namespace Support {

class Math
{
    private:
        Math();
        ~Math();

    public:
        static void pushTable(lua_State *l);

    public:
        static double logn(double n, unsigned int base);
        static double entropy(const ByteElaborator::CountResult&cr, uint64_t size);
        static double entropy(IO::DataBuffer* databuffer, uint64_t startoffset, uint64_t size);
        static double entropy(IO::DataBuffer* databuffer, uint64_t size);
        static double entropy(IO::DataBuffer* databuffer);

    lua_api:
        static int luaLogn(lua_State* l);
        static int luaEntropy(lua_State* l);
};

} // namespace Support
} // namespace PrefLib

#endif // PREFLIB_SUPPORT_MATH_H
