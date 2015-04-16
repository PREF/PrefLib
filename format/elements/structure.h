#ifndef PREFLIB_FORMAT_STRUCTURE_H
#define PREFLIB_FORMAT_STRUCTURE_H

#include "core/lua/luax.h"
#include "formatelement.h"
#include "field.h"
#include "fieldarray.h"

namespace PrefLib {
namespace Format {

using namespace Core;

class Structure: public FormatElement
{
    public:
        Structure(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, const char* name, FormatElement* parent = nullptr, lua_State* thread = nullptr);
        ~Structure();

    public:
        virtual uint64_t size();
        Structure* addStructure(const char* name);
        Field* addField(DataType::Type datatype, const char* name);
        Field* addField(DataType::Type datatype, const char* name, DataValue& valid);
        Field* addField(DataType::Type datatype, const char* name, LuaTable& valid);
        FieldArray* addArray(DataType::Type elementtype, const char* name, uint64_t count);

    public:
        FormatElement* field(int i);
        FormatElement* field(const char* name);
        FormatElement* firstField();
        FormatElement* lastField();

    protected:
        virtual FormatElement::Type type() const;

    lua_api:
        static int luaAddStructure(lua_State* l);
        static int luaAddField(lua_State* l);
        static int luaAddArray(lua_State* l);
};

} // namespace Format
} // namespace PrefLib

#endif // PREFLIB_FORMAT_STRUCTURE_H
