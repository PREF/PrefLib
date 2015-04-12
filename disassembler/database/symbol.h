#ifndef PREFLIB_DISASSEMBLER_SYMBOL_H
#define PREFLIB_DISASSEMBLER_SYMBOL_H

#include <cstdio>
#include <cstdint>

namespace PrefLib {
namespace Disassembler {

#define SYMBOL_NAME_MAXLENGTH 256

enum SymbolType
{
    COMMENT  = 0x00,
    BOOKMARK = 0x01,
    SYMBOL   = 0x02,
    LABEL    = 0x03,
    FUNCTION = 0x04,
};

struct Symbol
{
    uint8_t Type;
    uint8_t Length;
    uint64_t Address;
    char Name[SYMBOL_NAME_MAXLENGTH];
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_SYMBOL_H

