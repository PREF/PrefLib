#ifndef PREFLIB_FORMAT_FIELDARRAY_H
#define PREFLIB_FORMAT_FIELDARRAY_H

#include "fieldelement.h"
#include "field.h"

namespace PrefLib {
namespace Format {

class FieldArray : public FieldElement
{
    public:
        FieldArray(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type elementtype, const char* name, uint64_t userlength, FormatElement* parent, lua_State* thread = nullptr);
        ~FieldArray();
        Field* item(int i);
        Field* firstItem();
        Field* lastItem();
        DataType::Type elementType() const;
        virtual uint64_t size();
        virtual size_t length() const;

    protected:
        virtual FormatElement::Type type() const;
        virtual bool parseDynamic(const char **errmsg = nullptr);

    private:
        DataType::Type _elementtype;
        uint64_t _userlength;
};

} // namespace Format
} // namespace PrefLib

#endif // PREFLIB_FORMAT_FIELDARRAY_H
