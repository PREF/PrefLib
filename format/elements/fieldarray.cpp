#include "fieldarray.h"

namespace PrefLib {
namespace Format {

FieldArray::FieldArray(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type elementtype, const char *name, uint64_t userlength, FormatElement *parent, lua_State *thread): FieldElement(formattree, databuffer, offset, DataType::Array, name, parent, thread), _userlength(userlength)
{
    this->_dynamic = elementtype != DataType::Blob;

    this->setInteger("elementtype", elementtype);
}

FieldArray::~FieldArray()
{
    if(this->elementType() == DataType::Blob)
        return;

    for(size_t i = 0; i < this->length(); i++)
    {
        Field* field = this->item(i);
        this->unbindTable(i, field->name());
        delete field;
    }
}

Field *FieldArray::item(int i)
{
    this->parseDynamic();
    return dynamic_cast<Field*>(this->bindedTable(i));
}

Field *FieldArray::firstItem()
{
    this->parseDynamic();
    return dynamic_cast<Field*>(this->firstBindedTable());
}

Field *FieldArray::lastItem()
{
    this->parseDynamic();
    return dynamic_cast<Field*>(this->lastBindedTable());
}

FormatElement::Type FieldArray::type() const
{
    return FormatElement::FieldArrayType;
}

bool FieldArray::parseDynamic(const char** errmsg)
{
    (void)errmsg; /* Unused Parameter */

    if(!this->_dynamic)
        return true;

    this->_dynamic = false;
    uint64_t offset = this->offset();
    size_t elementsize = DataType::sizeOf(this->elementType());

    const char* arrayname = this->name();
    int namelen = strlen(arrayname) + sizeof(uintmax_t);
    char* elementname = new char[namelen + 1];
    elementname[namelen] = '\0';

    for(uint64_t i = 0; i < this->_userlength; i++, offset += elementsize)
    {
        int len = snprintf(elementname, namelen, "%s[%" PRIu64 "]", arrayname, i);
        elementname[len] = '\0';

        Field* f = new Field(this->tree(), this->_databuffer, offset, this->elementType(), elementname, this);
        this->bindTable(elementname, f);
    }

    delete[] elementname;
    return true;
}

uint64_t FieldArray::size()
{
    return DataType::sizeOf(this->elementType()) * this->_userlength;
}

size_t FieldArray::length() const
{
    int len = FieldElement::length();

    if(!len)
        return this->_userlength;

    return len;
}

DataValue FieldArray::value()
{
    if(this->elementType() == DataType::Character)
    {
        if(!this->parseDynamic())
            return DataValue();

        IO::DataBuffer* databuffer = this->dataBuffer();
        size_t len = this->length();
        char* data = new char[len + 1];

        data[len] = '\0';
        databuffer->read(this->offset(), reinterpret_cast<unsigned char*>(data), this->length());

        DataValue dv = data;
        delete[] data;
        return dv;
    }

    return DataValue();
}

DataType::Type FieldArray::elementType() const
{
    return static_cast<DataType::Type>(this->getInteger("elementtype"));
}

} // namespace Format
} // namespace PrefLib

