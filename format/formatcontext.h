#ifndef PREFLIB_FORMAT_FORMATCONTEXT_H
#define PREFLIB_FORMAT_FORMATCONTEXT_H

#include <lua.hpp>
#include "core/lua/luatable.h"
#include "categorycontext.h"
#include "formatdefinition.h"

namespace PrefLib {
namespace Format {

using namespace Core;

class FormatContext: public LuaTable
{
    public:
        FormatContext();
        ~FormatContext();

    public:
        FormatDefinition* get(int idx) const;
        const CategoryContext* categories() const;

    lua_api:
        static int luaCreate(lua_State *l);

    private:
        CategoryContext* _categoryctx;
};

} // namespace Format
} // namespace PrefLib

#endif // PREFLIB_FORMAT_FORMATCONTEXT_H
