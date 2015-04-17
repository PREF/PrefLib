#ifndef PREFLIB_FORMAT_FIELDELEMENT_H
#define PREFLIB_FORMAT_FIELDELEMENT_H

#include "formatelement.h"
#include "../../types/datatype.h"

namespace PrefLib {
namespace Format {

class FieldElement: public FormatElement, public ValuedField
{
    public:
        FieldElement(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent, lua_State* thread = nullptr);
        FieldElement(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent, DataValue &valid, lua_State* thread = nullptr);
        FieldElement(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent, LuaTable &valid, lua_State* thread = nullptr);
        ~FieldElement();

    public:
        DataType::Type dataType() const;
        virtual uint64_t size();

    protected:
        virtual int metaIndex(lua_State *l);
        virtual int metaNewIndex(lua_State *l);
};

} // namespace Format
} // namespace PrefLib

#endif // PREFLIB_FORMAT_FIELDELEMENT_H
