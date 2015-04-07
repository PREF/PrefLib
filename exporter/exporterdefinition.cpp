#include "exporterdefinition.h"

namespace PrefLib {
namespace Exporter {

ExporterDefinition::ExporterDefinition(const char *name, const char *description, const char *author, const char *version): LuaTable()
{
    this->push();
    this->setString("name", name);
    this->setString("description", description);
    this->setString("author", author);
    this->setString("version", version);
    lua_pop(LuaState::instance(), 1);
}

ExporterDefinition::~ExporterDefinition()
{

}

const char *ExporterDefinition::name() const
{
    return this->getString("name");
}

const char *ExporterDefinition::description() const
{
    return this->getString("description");
}

const char *ExporterDefinition::author() const
{
    return this->getString("author");
}

const char *ExporterDefinition::version() const
{
    return this->getString("version");
}

void ExporterDefinition::dump(IO::DataBuffer *databufferin, IO::DataBuffer *databufferout, uint64_t startoffset, uint64_t endoffset)
{
    if(!this->hasField("dump"))
        return;

    lua_State* l = LuaState::instance();
    this->push();

    lua_getfield(l, -1, "dump");
    this->push(); /* Self */
    databufferin->push();
    databufferout->push();
    lua_pushinteger(l, startoffset);
    lua_pushinteger(l, (!endoffset ? databufferin->length() : endoffset));
    this->protectedCall(5, 0);

    lua_pop(l, 1);
}

} // namespace Exporter
} // namespace PrefLib

