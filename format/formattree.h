#ifndef PREFLIB_FORMAT_FORMATTREE_H
#define PREFLIB_FORMAT_FORMATTREE_H

#include "core/lua/luatable.h"
#include "elements/structure.h"
#include "../io/databuffer.h"

namespace PrefLib {
namespace Format {

using namespace Core;

class FormatTree: public LuaTable
{
    public:
        FormatTree(IO::DataBuffer* databuffer, uint64_t baseoffset);
        ~FormatTree();

    public:
        Structure* addStructure(const char* name);
        Structure* addStructure(const char* name, uint64_t offset);
        IO::DataBuffer* dataBuffer() const;
        uint64_t baseOffset() const;
        FormatElement* element(int i) const;
        FormatElement* element(const char* name) const;
        FormatElement* firstElement() const;
        FormatElement* lastElement();
        bool isEmpty();

    lua_api:
        static int luaAddStructure(lua_State* l);
};

} // namespace Format
} // namespace PrefLib

#endif // PREFLIB_FORMAT_FORMATTREE_H
