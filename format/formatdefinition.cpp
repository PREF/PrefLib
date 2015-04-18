#include "formatdefinition.h"

namespace PrefLib {
namespace Format {

FormatDefinition::FormatDefinition(const char *category, const char* name, const char* author, const char* version, lua_State *thread): LuaTable(thread)
{
    this->setString("category", category);
    this->setString("name", name);
    this->setString("author", author);
    this->setString("version", version);
    this->setFunction("createTree", &FormatDefinition::luaCreateTree);
}

FormatDefinition::~FormatDefinition()
{

}

FormatTree* FormatDefinition::build(IO::DataBuffer *databuffer, uint64_t baseoffset)
{
    if(!this->hasField("build"))
        return nullptr;

    this->push();

    lua_getfield(this->_thread, -1, "build");
    this->push(); // Self
    databuffer->push();
    lua_pushinteger(this->_thread, baseoffset);
    this->protectedCall(3, 1);

    FormatTree* formattree = nullptr;

    if(!lua_isnoneornil(this->_thread, -1))
        formattree = reinterpret_cast<FormatTree*>(checkThis(this->_thread, -1));

    lua_pop(this->_thread, 2);
    return formattree;
}

const char *FormatDefinition::category() const
{
    return this->getString("category");
}

const char *FormatDefinition::name() const
{
    return this->getString("name");
}

const char *FormatDefinition::author() const
{
    return this->getString("author");
}

const char *FormatDefinition::version() const
{
    return this->getString("version");
}

int FormatDefinition::luaCreateTree(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 3);

    FormatTree* formattree = new FormatTree(reinterpret_cast<IO::DataBuffer*>(checkThis(l, 2)), luaL_checkinteger(l, 3), l);
    formattree->push();
    return 1;
}

} // namespace Format
} // namespace PrefLib

