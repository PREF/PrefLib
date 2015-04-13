#include "formatelement.h"

namespace PrefLib {
namespace Format {

using namespace Core;

FormatElement::FormatElement(FormatTree* formattree, IO::DataBuffer *databuffer, uint64_t offset, const char *name, FormatElement *parent): LuaTable(), _databuffer(databuffer), _dynamic(false), _base(16), _infocallback({ false, 0 })
{
    this->setInteger("offset", offset);
    this->setString("name", name);
    this->setTable("tree", reinterpret_cast<LuaTable*>(formattree));
    this->setFunction("infoProvider", &FormatElement::luaInfoProvider);
    this->setFunction("dynamic", &FormatElement::luaDynamic);

    if(parent)
        this->setTable("parent", parent);

    lua_State* l = LuaState::instance();
    this->push();

    if(luaL_newmetatable(l, "formatelement"))
    {
        lua_pushcfunction(l, &FormatElement::luaMetaIndex);
        lua_setfield(l, -2, "__index");

        lua_pushcfunction(l, &FormatElement::luaMetaNewIndex);
        lua_setfield(l, -2, "__newindex");

        lua_pushcfunction(l, &FormatElement::luaMetaLength);
        lua_setfield(l, -2, "__len");
    }

    lua_setmetatable(l, -2);
    lua_pop(l, 1);
}

FormatElement::~FormatElement()
{
    if(this->_infocallback.Lua && this->_infocallback.IsLua)
    {
        luaL_unref(LuaState::instance(), LUA_REGISTRYINDEX, this->_infocallback.Lua);

        /* Reset Callback Information */
        this->_infocallback.IsLua = false;
        this->_infocallback.Cpp = nullptr;
    }
}

int FormatElement::luaDynamic(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 2);

    FormatElement* thethis = reinterpret_cast<FormatElement*>(checkThis(l, 1));
    luaL_checktype(l, 2, LUA_TFUNCTION);

    lua_pushvalue(l, 2);
    thethis->_dynamic = true;
    thethis->_dynamiccallback.Lua = luaL_ref(l, LUA_REGISTRYINDEX);
    thethis->_dynamiccallback.IsLua = true;

    thethis->push(); /* For Chaining */
    return 1;
}

int FormatElement::luaInfoProvider(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 2);

    FormatElement* thethis = reinterpret_cast<FormatElement*>(checkThis(l, 1));
    luaL_checktype(l, 2, LUA_TFUNCTION);

    lua_pushvalue(l, 2);
    thethis->_infocallback.Lua = luaL_ref(l, LUA_REGISTRYINDEX);
    thethis->_infocallback.IsLua = true;

    thethis->push(); /* For Chaining */
    return 1;
}

int FormatElement::luaMetaIndex(lua_State *l)
{
    FormatElement* thethis = reinterpret_cast<FormatElement*>(checkThis(l, 1));
    return thethis->metaIndex(l);
}

int FormatElement::luaMetaNewIndex(lua_State *l)
{
    FormatElement* thethis = reinterpret_cast<FormatElement*>(checkThis(l, 1));
    return thethis->metaNewIndex(l);
}

int FormatElement::luaMetaLength(lua_State *l)
{
    FormatElement* thethis = reinterpret_cast<FormatElement*>(checkThis(l, 1));
    return thethis->metaLength(l);
}

bool FormatElement::isDynamic() const
{
    return this->_dynamic;
}

bool FormatElement::isStructure() const
{
    return this->type() == FormatElement::StructureType;
}

bool FormatElement::isField() const
{
    return (this->type() == FormatElement::FieldType) || (this->type() == FormatElement::FieldArrayType);
}

bool FormatElement::isFieldArray() const
{
    return this->type() == FormatElement::FieldArrayType;
}

bool FormatElement::isBitField() const
{
    return this->type() == FormatElement::BitFieldType;
}

IO::DataBuffer *FormatElement::dataBuffer() const
{
    return this->_databuffer;
}

int FormatElement::metaIndex(lua_State *l)
{
    const char* arg = luaL_checkstring(l, 2);

    if(!strcmp(arg, "size"))
    {
        lua_pushinteger(l, this->size());
        return 1;
    }

    if(!strcmp(arg, "base"))
    {
        lua_pushinteger(l, this->base());
        return 1;
    }

    if(!strcmp(arg, "info"))
    {
        lua_pushstring(l, this->info());
        return 1;
    }

    return 0;
}

int FormatElement::metaNewIndex(lua_State *l)
{
    const char* arg = luaL_checkstring(l, 2);

    if(!strcmp(arg, "base"))
        this->setBase(luaL_checkinteger(l, 3));

    return 0;
}

int FormatElement::metaLength(lua_State *l)
{
    lua_pushinteger(l, this->length());
    return 1;
}

bool FormatElement::parseDynamic(const char** errmsg)
{
    if(!this->_dynamic || !this->_dynamiccallback.Cpp || this->length())
        return true;

    if(!this->_dynamiccallback.IsLua)
    {
        this->_dynamiccallback.Cpp(this);
        return true;
    }

    lua_State* l = LuaState::instance();
    lua_rawgeti(l, LUA_REGISTRYINDEX, this->_dynamiccallback.Lua);
    this->push();

    int err = lua_pcall(l, 1, 0, 0);

    if(err)
    {
        if(errmsg)
            *errmsg = lua_tostring(l, -1);
        else
            luaL_error(l, lua_tostring(l, -1));

        lua_pop(l, 1);
        return false;
    }

    return true;
}

uint64_t FormatElement::offset() const
{
    return this->getInteger("offset");
}

uint64_t FormatElement::endOffset()
{
    return this->offset() + this->size();
}

uint64_t FormatElement::base() const
{
    return this->_base;
}

const char *FormatElement::info()
{
    if(!this->_infocallback.Cpp)
        return nullptr;

    if(!this->_infocallback.IsLua)
        return this->_infocallback.Cpp(this);

    lua_State* l = LuaState::instance();
    lua_rawgeti(l, LUA_REGISTRYINDEX, this->_infocallback.Lua);
    this->push();
    lua_pcall(l, 1, 1, 0);

    const char* infostring = lua_tostring(l, -1);
    lua_pop(l, 1);
    return infostring;
}

const char *FormatElement::name() const
{
    return this->getString("name");
}

FormatTree *FormatElement::tree() const
{
    return reinterpret_cast<FormatTree*>(this->getTable("tree"));
}

FormatElement *FormatElement::parent() const
{
    if(!this->hasField("parent"))
        return nullptr;

    return dynamic_cast<FormatElement*>(this->getTable("parent"));
}

void FormatElement::setBase(uint64_t base)
{
    this->_base = base;
}

void FormatElement::setInfoProvider(FieldCallback infocallback)
{
    this->_infocallback.IsLua = false;
    this->_infocallback.Cpp = infocallback;
}

void FormatElement::setDynamic(FormatElement::FieldCallback dynamiccallback)
{
    this->_dynamic = true;
    this->_dynamiccallback.IsLua = false;
    this->_dynamiccallback.Cpp = dynamiccallback;
}

void FormatElement::populate()
{
    if(!this->_dynamic)
        return;

    const char* msg = nullptr;

    if(!this->parseDynamic(&msg))
        throw std::runtime_error(msg);
}

} // namespace Format
} // namespace PrefLib
