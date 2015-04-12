#ifndef PREFLIB_FORMAT_BITFIELD_H
#define PREFLIB_FORMAT_BITFIELD_H

#include "fieldelement.h"

namespace PrefLib {
namespace Format {

class BitField: public FieldElement, public ValuedField
{
    public:
        BitField(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, DataType::Type datatype, const char* name, int bitstart, int bitend, FormatElement* parent);
        ~BitField();

    protected:
        virtual FormatElement::Type type() const;

    private:
        uint64_t createMask();

    public:
        virtual uintmax_t size();
        size_t bitstart() const;
        size_t bitend() const;
        virtual DataValue value();

    private:
        int _lastbitstart;
        int _lastbitend;
};

} // namespace Format
} // namespace PrefLib

#endif // PREFLIB_FORMAT_BITFIELD_H
