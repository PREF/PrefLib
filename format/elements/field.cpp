#include "field.h"

namespace PrefLib {
namespace Format {

Field::Field(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char *name, FormatElement *parent, lua_State *thread): FieldElement(formattree, databuffer, offset, datatype, name, parent, thread)
{
    this->setFunction("setBitField", &Field::luaSetBitField);
}

Field::Field(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, FormatElement* parent, DataValue& valid, lua_State *thread): Field(formattree, databuffer, offset, datatype, name, parent, thread)
{
    DataValue v = this->value();

    if(v != valid)
        luaL_error(this->_thread, "Field '%s': Expected 0x%s, got 0x%s", name, valid.toString(16), v.toString(16));
}

Field::Field(FormatTree* formattree, IO::DataBuffer *databuffer, uint64_t offset, DataType::Type datatype, const char *name, FormatElement *parent, LuaTable &valid, lua_State *thread): Field(formattree, databuffer, offset, datatype, name, parent, thread)
{
    DataValue v = this->value();

    for(size_t i = 0; i < valid.length(); i++)
    {
        if(v == valid.getI<lua_Integer>(i))
            return;
    }

    luaL_error(this->_thread, "Field '%s': 0x%s is not valid", name, v.toString(16));
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

BitField *Field::setBitField(const char *name, uint64_t bitstart, uint64_t bitend, DataValue &valid)
{
    BitField* bf = new BitField(this->tree(), this->_databuffer, this->offset(), this->dataType(), name, bitstart, bitend, this, valid, this->thread());
    this->bindTable(name, bf);
    return bf;
}

BitField *Field::setBitField(const char *name, uint64_t bitstart, uint64_t bitend, LuaTable &valid)
{
    BitField* bf = new BitField(this->tree(), this->_databuffer, this->offset(), this->dataType(), name, bitstart, bitend, this, valid, this->thread());
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

    BitField* bf = nullptr;
    lua_Integer bitstart = luaL_checkinteger(l, 3);

    if(argc > 4)
    {
        int t = lua_type(l, 5);

        if((t != LUA_TNUMBER) && (t != LUA_TTABLE))
            luaL_error(l, "Field.setBitField(): Expected 'number' or 'table', '%s' given", lua_typename(l, t));

        if(t == LUA_TNUMBER)
        {
            DataValue valid = lua_tointeger(l, 5);
            bf = thethis->setBitField(luaL_checkstring(l, 2), bitstart, luaL_checkinteger(l, 4), valid);
        }
        else // if(t == LUA_TTABLE)
        {
            LuaTable valid(l, 5);
            bf = thethis->setBitField(luaL_checkstring(l, 2), bitstart, luaL_checkinteger(l, 4), valid);
        }
    }
    else
        bf = thethis->setBitField(luaL_checkstring(l, 2), bitstart, luaL_optinteger(l, 4, bitstart));

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

FormatElement::Type Field::type() const
{
    return FormatElement::FieldType;
}

} // namespace Format
} // namespace PrefLib

