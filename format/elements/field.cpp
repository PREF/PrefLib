#include "field.h"

namespace PrefLib {
namespace Format {

Field::Field(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char *name, FormatElement *parent): FieldElement(formattree, databuffer, offset, datatype, name, parent)
{

}

Field::Field(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent, DataValue& valid): FieldElement(formattree, databuffer, offset, datatype, name, parent, valid)
{

}

Field::Field(FormatTree* formattree, IO::DataBuffer *databuffer, uint64_t offset, DataType::Type datatype, const char *name, FormatElement *parent, LuaTable &valid): FieldElement(formattree, databuffer, offset, datatype, name, parent, valid)
{

}

Field::~Field()
{

}

DataValue Field::value()
{
    IO::DataBuffer* databuffer = this->dataBuffer();
    DataValue dv = 0;
    databuffer->read(this->offset(), &dv, this->size());
    dv.castTo(this->dataType());
    return dv;
}

int Field::metaIndex(lua_State *l)
{
    const char* arg = luaL_checkstring(l, 2);

    if(!strcmp(arg, "value"))
    {
        DataValue dv = this->value();
        dv.push();
        return 1;
    }

    return FieldElement::metaIndex(l);
}

int Field::metaNewIndex(lua_State *l)
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

FormatElement::Type Field::type() const
{
    return FormatElement::FieldType;
}

} // namespace Format
} // namespace PrefLib

