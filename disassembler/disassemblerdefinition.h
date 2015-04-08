#ifndef PREFLIB_DISASSEMBLER_DISASSEMBLERDEFINITION_H
#define PREFLIB_DISASSEMBLER_DISASSEMBLERDEFINITION_H

#include "../core/luatable.h"
#include "../format/formatdefinition.h"
#include "disassemblerlisting.h"

namespace PrefLib {
namespace Disassembler {

using namespace Core;

class DisassemblerDefinition: public LuaTable
{
    public:
        DisassemblerDefinition(const char* name, Format::FormatDefinition* formatdefinition, DataType::Type addresstype, const char* author, const char* version);
        ~DisassemblerDefinition();

    public:
        void initialize();
        void finalize();
        void map(DisassemblerListing* listing);
        void disassemble(DisassemblerListing *listing, DataValue &address);

    public:
        const char *name() const;
        const char* author() const;
        const char* version() const;
        const Format::FormatDefinition* format() const;
        DataType::Type addressType() const;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_DISASSEMBLERDEFINITION_H
