#include "formattree.h"

namespace PrefLib {
namespace Format {

FormatTree::FormatTree(IO::DataBuffer *databuffer, uint64_t baseoffset, lua_State *thread): LuaTable(thread)
{
    this->setInteger("baseoffset", baseoffset);
    this->setTable("databuffer", databuffer);
    this->setFunction("addStructure", &FormatTree::luaAddStructure);
}

FormatTree::~FormatTree()
{
    IO::DataBuffer* databuffer = this->dataBuffer();

    if(databuffer)
    {
        delete databuffer;
        this->setTable("databuffer", nullptr);
    }

    size_t len = this->length();

    for(size_t i = 0; i < len; i++)
    {
        FormatElement* element = this->element(i);
        this->unbindTable(i, element->name());
        delete element;
    }
}

Structure *FormatTree::addStructure(const char *name)
{
    return this->addStructure(name, (this->isEmpty() ? 0 : this->lastElement()->endOffset()));
}

Structure *FormatTree::addStructure(const char *name, uint64_t offset)
{
    Structure* s = new Structure(this, this->dataBuffer(), offset, name, nullptr, this->thread());
    this->bindTable(s->name(), s);
    return s;
}

IO::DataBuffer *FormatTree::dataBuffer() const
{
    return dynamic_cast<IO::DataBuffer*>(this->getTable("databuffer"));
}

uint64_t FormatTree::baseOffset() const
{
    return this->getInteger("baseoffset");
}

FormatElement *FormatTree::element(int i) const
{
    return dynamic_cast<FormatElement*>(this->bindedTable(i));
}

FormatElement *FormatTree::element(const char *name) const
{
    return dynamic_cast<FormatElement*>(this->bindedTable(name));
}

FormatElement *FormatTree::firstElement() const
{
    return dynamic_cast<FormatElement*>(this->firstBindedTable());
}

FormatElement *FormatTree::lastElement()
{
    return dynamic_cast<FormatElement*>(this->lastBindedTable());
}

bool FormatTree::isEmpty()
{
    return this->length() == 0;
}

int FormatTree::luaAddStructure(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectminargc(l, argc, 2);

    Structure* s = nullptr;
    FormatTree* thethis = reinterpret_cast<FormatTree*>(checkThis(l, 1));

    if(argc == 2)
        s = thethis->addStructure(luaL_checkstring(l, 2));
    else // if(argc >= 3)
        s = thethis->addStructure(luaL_checkstring(l, 2), luaL_checkinteger(l, 3));

    s->push();
    return 1;
}

} // namespace Format
} // namespace PrefLib

