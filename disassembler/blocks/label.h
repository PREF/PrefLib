#ifndef PREFLIB_DISASSEMBLER_LABEL_H
#define PREFLIB_DISASSEMBLER_LABEL_H

#include "block.h"

namespace PrefLib {
namespace Disassembler {

class Label: public Block
{
    public:
        Label(uint64_t startaddress, lua_State* thread = nullptr);

    protected:
        virtual Block::Type type() const;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_LABEL_H
