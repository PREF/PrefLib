#ifndef PREFLIB_DISASSEMBLER_DISASSEMBLERENGINE_H
#define PREFLIB_DISASSEMBLER_DISASSEMBLERENGINE_H

#include <stack>
#include "disassemblerdefinition.h"
#include "disassemblerlisting.h"

namespace PrefLib {
namespace Disassembler {

class DisassemblerEngine
{
    public:
        DisassemblerEngine(DisassemblerDefinition* definition);
        ~DisassemblerEngine();
        void disassemble(DisassemblerListing* listing);

    private:
        void prepareQueue(DisassemblerListing* listing);

    private:
        DisassemblerDefinition* _definition;
        std::stack<DataValue> _stack;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_DISASSEMBLERENGINE_H
