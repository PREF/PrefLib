#include "field.h"

namespace PrefLib {
namespace Format {

Field::Field(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char *name, FormatElement *parent, lua_State *thread): FieldElement(formattree, databuffer, offset, datatype, name, parent, thread)
{
    this->setFunction("setBitField", &Field::luaSetBitField);
}

Field::Field(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent, DataValue& valid, lua_State *thread): FieldElement(formattree, databuffer, offset, datatype, name, parent, valid, thread)
{

}

Field::Field(FormatTree* formattree, IO::DataBuffer *databuffer, uint64_t offset, DataType::Type datatype, const char *name, FormatElement *parent, LuaTable &valid, lua_State *thread): FieldElement(formattree, databuffer, offset, datatype, name, parent, valid, thread)
{

}

Field::~Field()
{
    size_t len = this->length();

    for(size_t i = 0; i < len; i++)
    {
        BitField* bitfield = this->bitField(i);
        this->unbindTable(i, bitfield->name());
        delete bitfield;
    }
}

BitField *Field::setBitField(const char *name, uint64_t bitstart, uint64_t bitend)
{
    BitField* bf = new BitField(this->tree(), this->_databuffer, this->offset(), this->dataType(), name, bitstart, bitend, this, this->thread());
    this->bindTable(name, bf);
    return bf;
}

BitField *Field::setBitField(const char *name, uint64_t bitstart)
{
    return this->setBitField(name, bitstart, bitstart);
}

int Field::luaSetBitField(lua_State* l)
{
    int argc = lua_gettop(l);
    luaX_expectminargc(l, argc, 3);

    Field* thethis = reinterpret_cast<Field*>(checkThis(l, 1));
    int bitstart = luaL_checkinteger(l, 3);
    BitField* bf = thethis->setBitField(luaL_checkstring(l, 2), bitstart, luaL_optinteger(l, 4, bitstart));
    bf->push();
    return 1;
}

DataValue Field::value()
{
    IO::DataBuffer* databuffer = this->dataBuffer();
    DataValue dv = 0;
    databuffer->read(this->offset(), &dv, this->size());
    dv.castTo(this->dataType());
    return dv;
}

BitField *Field::bitField(int i) const
{
    return dynamic_cast<BitField*>(this->bindedTable(i));
}

BitField *Field::bitField(const char *name) const
{
    return dynamic_cast<BitField*>(this->bindedTable(name));
}

int Field::metaIndex(lua_State *l)
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

