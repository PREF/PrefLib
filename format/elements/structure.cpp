#include "structure.h"

namespace PrefLib {
namespace Format {

Structure::Structure(FormatTree* formattree, IO::DataBuffer *databuffer, uint64_t offset, const char* name, FormatElement* parent): FormatElement(formattree, databuffer, offset, name, parent)
{
    this->setFunction("addStructure", &Structure::luaAddStructure);
    this->setFunction("addField", &Structure::luaAddField);
    this->setFunction("addArray", &Structure::luaAddArray);
}

Structure::~Structure()
{

}

uint64_t Structure::size()
{
    uint64_t sz = 0;

    for(size_t i = 0; i < this->length(); i++)
    {
        FormatElement* fe = this->field(i);
        sz += fe->size();
    }

    return sz;
}

Structure *Structure::addStructure(const char *name)
{
    Structure* s = new Structure(this->tree(), this->_databuffer, this->endOffset(), name, this);
    this->bindTable(name, s);
    return s;
}

Field *Structure::addField(DataType::Type datatype, const char *name)
{
    Field* f = new Field(this->tree(), this->_databuffer, this->endOffset(), datatype, name, this);
    this->bindTable(name, f);
    return f;
}

Field *Structure::addField(DataType::Type datatype, const char *name, DataValue& valid)
{
    Field* f = new Field(this->tree(), this->_databuffer, this->endOffset(), datatype, name, this, valid);
    this->bindTable(name, f);
    return f;
}

Field *Structure::addField(DataType::Type datatype, const char *name, LuaTable& valid)
{
    Field* f = new Field(this->tree(), this->_databuffer, this->endOffset(), datatype, name, this, valid);
    this->bindTable(name, f);
    return f;
}

FieldArray *Structure::addArray(DataType::Type elementtype, const char *name, uint64_t count)
{
    FieldArray* f = new FieldArray(this->tree(), this->_databuffer, this->endOffset(), elementtype, name, count, this);
    this->bindTable(name, f);
    return f;
}

FormatElement *Structure::field(int i)
{
    if(!this->parseDynamic())
        return nullptr;

    return dynamic_cast<FormatElement*>(this->bindedTable(i));
}

FormatElement *Structure::field(const char *name)
{
    if(!this->parseDynamic())
        return nullptr;

    return dynamic_cast<FormatElement*>(this->bindedTable(name));
}

FormatElement *Structure::firstField()
{
    if(!this->parseDynamic())
        return nullptr;

    return dynamic_cast<FormatElement*>(this->firstBindedTable());
}

FormatElement *Structure::lastField()
{
    if(!this->parseDynamic())
        return nullptr;

    return dynamic_cast<FormatElement*>(this->lastBindedTable());
}

FormatElement::Type Structure::type() const
{
    return FormatElement::StructureType;
}

int Structure::luaAddStructure(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 2);

    Structure* thethis = reinterpret_cast<Structure*>(checkThis(l, 1));
    Structure* s = thethis->addStructure(luaL_checkstring(l, 2));
    s->push();
    return 1;
}

int Structure::luaAddField(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectminargc(l, argc, 3);

    Field* f = nullptr;
    Structure* thethis = reinterpret_cast<Structure*>(checkThis(l, 1));

    if(argc >= 4)
    {
        int t = lua_type(l, 4);

        if((t != LUA_TNUMBER) && (t != LUA_TTABLE))
            luaL_error(l, "Structure.addField(): Expected 'number' or 'table', '%s' given", lua_typename(l, t));

        if(t == LUA_TNUMBER)
        {
            DataValue valid = lua_tointeger(l, 4);
            f = thethis->addField(static_cast<DataType::Type>(luaL_checkinteger(l, 2)), luaL_checkstring(l, 3), valid);
        }
        else // if(t == LUA_TTABLE)
        {
            LuaTable valid(4);
            f = thethis->addField(static_cast<DataType::Type>(luaL_checkinteger(l, 2)), luaL_checkstring(l, 3), valid);
        }
    }
    else
        f = thethis->addField(static_cast<DataType::Type>(luaL_checkinteger(l, 2)), luaL_checkstring(l, 3));

    f->push();
    return 1;
}

int Structure::luaAddArray(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 4);

    Structure* thethis = reinterpret_cast<Structure*>(checkThis(l, 1));
    FieldArray* f = thethis->addArray(static_cast<DataType::Type>(luaL_checkinteger(l, 2)), luaL_checkstring(l, 3), luaL_checkinteger(l, 4));

    f->push();
    return 1;
}

} // namespace Format
} // namespace PrefLib

