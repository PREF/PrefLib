#include "formatdefinition.h"

namespace PrefLib {
namespace Format {

FormatDefinition::FormatDefinition(const char *category, const char* name, const char* author, const char* version, lua_State *thread): LuaTable(thread)
{
    this->setString("category", category);
    this->setString("name", name);
    this->setString("author", author);
    this->setString("version", version);
}

FormatDefinition::~FormatDefinition()
{

}

FormatTree* FormatDefinition::build(IO::DataBuffer *databuffer, uint64_t baseoffset)
{
    if(!this->hasField("build"))
        return nullptr;

    FormatTree* formattree = new FormatTree(databuffer, baseoffset, this->_thread);
    this->push();

    lua_getfield(this->_thread, -1, "build");
    this->push(); // Self
    formattree->push();
    this->protectedCall(2, 0);

    lua_pop(this->_thread, 1);
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

} // namespace Format
} // namespace PrefLib

