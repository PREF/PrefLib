#ifndef PREFLIB_SUPPORT_ALGORITHM_H
#define PREFLIB_SUPPORT_ALGORITHM_H

#include "../core/lua/luax.h"
#include "../io/databuffer.h"
#include "byteelaborator.h"
#include "math.h"

namespace PrefLib {
namespace Support {

class Algorithm
{
    private:
        Algorithm();
        ~Algorithm();

    public:
        static void push(lua_State* l);

    public:
        static uint64_t rebase(uint64_t address, uint64_t oldbaseaddress, uint64_t newbaseaddress);
        static double entropy(const ByteElaborator::CountResult&cr, uint64_t size);
        static double entropy(IO::DataBuffer* databuffer, uint64_t startoffset, uint64_t size, volatile bool* cancontinue = nullptr);
        static double entropy(IO::DataBuffer* databuffer, uint64_t size, volatile bool* cancontinue = nullptr);
        static double entropy(IO::DataBuffer* databuffer, volatile bool* cancontinue = nullptr);

    lua_api:
        static int luaEntropy(lua_State* l);
        static int luaRebase(lua_State* l);
};

} // namespace Support
} // namespace PrefLib

#endif // PREFLIB_SUPPORT_ALGORITHM_H
