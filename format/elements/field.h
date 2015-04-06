#ifndef PREFLIB_FORMAT_FIELD_H
#define PREFLIB_FORMAT_FIELD_H

#include "fieldelement.h"
#include "bitfield.h"

namespace PrefLib {
namespace Format {

using namespace Core;

class Field: public FieldElement, public ValuedField
{
    public:
        Field(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent);
        Field(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent, DataValue& valid);
        Field(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent, LuaTable& valid);
        ~Field();

    public:
        virtual DataValue value();
        BitField* setBitField(const char* name, uint64_t bitstart, uint64_t bitend);
        BitField* setBitField(const char* name, uint64_t bitstart);

    lua_api:
        static int luaSetBitField(lua_State*l);

    protected:
        virtual FormatElement::Type type() const;
        virtual int metaIndex(lua_State *l);
        virtual int metaNewIndex(lua_State *l);
};

} // namespace Format
} // namespace PrefLib

#endif // PREFLIB_FORMAT_FIELD_H
