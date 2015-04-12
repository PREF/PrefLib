#ifndef PREFLIB_FORMAT_FORMATDEFINITION_H
#define PREFLIB_FORMAT_FORMATDEFINITION_H

#include "core/lua/luatable.h"
#include "elements/structure.h"
#include "formattree.h"
#include "../io/databuffer.h"

namespace PrefLib {
namespace Format {

using namespace Core;

class FormatDefinition: public LuaTable
{
    public:
        FormatDefinition(const char* category, const char *name, const char *version, const char *author);
        virtual ~FormatDefinition();

    public:
        FormatTree* build(IO::DataBuffer* databuffer, uint64_t baseoffset = 0) const;
        const char* category() const;
        const char* name() const;
        const char* author() const;
        const char* version() const;

    lua_api:
        static int luaCreateTree(lua_State *l);
};

} // namespace Format
} // namespace PrefLib

#endif // PREFLIB_FORMAT_FORMATDEFINITION_H
