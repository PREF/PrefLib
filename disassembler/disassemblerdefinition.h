#ifndef PREFLIB_DISASSEMBLER_DISASSEMBLERDEFINITION_H
#define PREFLIB_DISASSEMBLER_DISASSEMBLERDEFINITION_H

#include <capstone.h>
#include "../core/luatable.h"
#include "../format/formatdefinition.h"
#include "blocks/block.h"
#include "disassemblerlisting.h"
#include "listingprinter.h"

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
        DataValue disassemble(LuaTable* engine, DisassemblerListing *listing, DataValue &address);
        void output(ListingPrinter* printer, Instruction* instruction);

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
