#ifndef PREFLIB_DISASSEMBLER_CAPSTONEINSTRUCTION_H
#define PREFLIB_DISASSEMBLER_CAPSTONEINSTRUCTION_H

#include "instruction.h"
#include <capstone.h>

namespace PrefLib {
namespace Disassembler {

class CapstoneInstruction: public Instruction
{
    public:
        CapstoneInstruction(csh handle, cs_insn* insn, int csinsnref, lua_State* thread = nullptr);
        ~CapstoneInstruction();

    protected:
        virtual int metaIndex(lua_State *l);

    private:
        csh _handle;
        cs_insn* _insn;
        int _csinsinref;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_CAPSTONEINSTRUCTION_H
