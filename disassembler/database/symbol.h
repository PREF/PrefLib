#ifndef PREFLIB_DISASSEMBLER_SYMBOL_H
#define PREFLIB_DISASSEMBLER_SYMBOL_H

#include <cstdio>
#include <cstdint>

namespace PrefLib {
namespace Disassembler {

#define SYMBOL_NAME_MAXLENGTH 256

struct Symbol
{
    uint8_t Type;
    uint8_t Length;
    char Name[SYMBOL_NAME_MAXLENGTH];
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_SYMBOL_H

