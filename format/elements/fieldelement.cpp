#include "fieldelement.h"

namespace PrefLib {
namespace Format {

FieldElement::FieldElement(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char *name, FormatElement *parent, lua_State *thread): FormatElement(formattree, databuffer, offset, name, parent, thread)
{
    this->setInteger("datatype", datatype);
}

FieldElement::~FieldElement()
{

}

DataType::Type FieldElement::dataType() const
{
    return static_cast<DataType::Type>(this->getInteger("datatype"));
}

uint64_t FieldElement::size()
{
    return DataType::sizeOf(this->dataType());
}

int FieldElement::metaIndex(lua_State *l)
{
    const char* arg = luaL_checkstring(l, 2);

    if(!strcmp(arg, "value"))
    {
        DataValue dv = this->value();
        dv.push(l);
        return 1;
    }

    return FieldElement::metaIndex(l);
}

int FieldElement::metaNewIndex(lua_State *l)
{
    const char* arg = luaL_checkstring(l, 2);

    if(!strcmp(arg, "value"))
    {
        IO::DataBuffer* databuffer = this->dataBuffer();
        DataValue dv = this->value();
        databuffer->write(this->offset(), &dv, this->size());
    }

    return FieldElement::metaNewIndex(l);
}

} // namespace Format
} // namespace PrefLib

