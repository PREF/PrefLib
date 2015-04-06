#include "bitfield.h"

namespace PrefLib {
namespace Format {

BitField::BitField(FormatTree *formattree, IO::DataBuffer *databuffer, uint64_t offset, DataType::Type datatype, const char *name, int bitstart, int bitend, FormatElement *parent): FieldElement(formattree, databuffer, offset, datatype, name, parent)
{
    this->setInteger("bitstart", bitstart);
    this->setInteger("bitend", bitend);
}

BitField::~BitField()
{

}

FormatElement::Type BitField::type() const
{
    return FormatElement::BitFieldType;
}

uint64_t BitField::createMask()
{
    uintmax_t mask = 0u;
    size_t bitstart = this->bitstart(), bitend = this->bitend(), fieldsize = DataType::bitWidth(dynamic_cast<FieldElement*>(this->parent())->dataType());

    for(size_t i = 0; i < fieldsize; i++)
    {
        if((i >= bitstart) && (i <= bitend))
            mask |= 1u << i;
        else
            mask |= 0u << i;
    }

    return mask;
}

uintmax_t BitField::size()
{
    return 1; /* No Size for Bitfields */
}

size_t BitField::bitstart() const
{
    return this->getInteger("bitstart");
}

size_t BitField::bitend() const
{
    return this->getInteger("bitend");
}

DataValue BitField::value()
{
    uintmax_t mask = this->createMask();
    ValuedField* field = dynamic_cast<ValuedField*>(this->parent());
    return (field->value() & mask) >> this->bitstart();
}

} // namespace Format
} // namespace PrefLib

