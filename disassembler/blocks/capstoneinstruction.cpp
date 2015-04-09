#include "capstoneinstruction.h"

namespace PrefLib {
namespace Disassembler {

CapstoneInstruction::CapstoneInstruction(csh handle, cs_insn *insn): Instruction(insn->address, insn->size, insn->mnemonic, cs_insn_group(handle, insn, CS_GRP_JUMP), cs_insn_group(handle, insn, CS_GRP_CALL), false), _handle(handle), _insn(insn)
{

}

CapstoneInstruction::~CapstoneInstruction()
{
    if(this->_insn)
    {
        cs_free(this->_insn, 1);
        this->_insn = nullptr;
    }
}

} // namespace Disassembler
} // namespace PrefLib

