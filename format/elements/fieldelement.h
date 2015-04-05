#ifndef PREFLIB_FORMAT_FIELDELEMENT_H
#define PREFLIB_FORMAT_FIELDELEMENT_H

#include "formatelement.h"
#include "../../types/datatype.h"

namespace PrefLib {
namespace Format {

class FieldElement: public FormatElement
{
    public:
        FieldElement(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent);
        FieldElement(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent, DataValue &valid);
        FieldElement(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent, LuaTable &valid);
        ~FieldElement();

    public:
        DataType::Type dataType() const;
        virtual uint64_t size();
};

} // namespace Format
} // namespace PrefLib

#endif // PREFLIB_FORMAT_FIELDELEMENT_H
