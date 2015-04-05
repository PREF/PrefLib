#ifndef PREFLIB_FORMAT_FIELD_H
#define PREFLIB_FORMAT_FIELD_H

#include "fieldelement.h"

namespace PrefLib {
namespace Format {

using namespace Core;

class Field: public FieldElement
{
    public:
        Field(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent);
        Field(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent, DataValue& valid);
        Field(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent, LuaTable& valid);
        ~Field();

    protected:
        virtual FormatElement::Type type() const;
        virtual int metaIndex(lua_State *l);
        virtual int metaNewIndex(lua_State *l);

    public:
        DataValue value();
};

} // namespace Format
} // namespace PrefLib

#endif // PREFLIB_FORMAT_FIELD_H
