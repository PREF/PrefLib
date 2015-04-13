#include "fieldelement.h"

namespace PrefLib {
namespace Format {

FieldElement::FieldElement(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char *name, FormatElement *parent): FormatElement(formattree, databuffer, offset, name, parent)
{
    this->setInteger("datatype", datatype);
}

FieldElement::FieldElement(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char *name, FormatElement *parent, DataValue& valid): FieldElement(formattree, databuffer, offset, datatype, name, parent)
{
    DataValue v = 0;
    databuffer->read(offset, &v, DataType::sizeOf(datatype));

    if(v != valid)
        luaL_error(LuaState::instance(), "Field '%s': Expected 0x%s, got 0x%s", name, valid.toString(16), v.toString(16));
}

FieldElement::FieldElement(FormatTree* formattree, IO::DataBuffer *databuffer, uint64_t offset, DataType::Type datatype, const char *name, FormatElement *parent, LuaTable& valid): FieldElement(formattree, databuffer, offset, datatype, name, parent)
{
    DataValue v = 0;
    databuffer->read(offset, &v, DataType::sizeOf(datatype));

    for(size_t i = 1; i <= valid.length(); i++)
    {
        if(v == valid.getI<lua_Integer>(i))
            return;
    }

    luaL_error(LuaState::instance(), "Field '%s': 0x%s is not valid", name, v.toString(16));
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

} // namespace Format
} // namespace PrefLib

