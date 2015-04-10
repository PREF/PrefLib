#ifndef PREFLIB_DISASSEMBLER_INSTRUCTION_H
#define PREFLIB_DISASSEMBLER_INSTRUCTION_H

#include "block.h"

namespace PrefLib {
namespace Disassembler {

class Instruction: public Block
{
    public:
        Instruction(uint64_t address);
        ~Instruction();

    private:
        static char* uppercase(char* s);

    protected:
        Instruction(uint64_t address, uint64_t size, char *mnemonic, bool isjump, bool iscall, bool isconditional);

    public:
        const char* mnemonic() const;
        uint64_t destination() const;
        bool isBranch() const;
        bool isJump() const;
        bool isCall() const;
        bool isConditional() const;
        bool isDestinationValid() const;

    protected:
        virtual Block::Type type() const;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_INSTRUCTION_H
