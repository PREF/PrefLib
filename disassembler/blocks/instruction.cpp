#include "instruction.h"

namespace PrefLib {
namespace Disassembler {

Instruction::Instruction(uint64_t address): Instruction(address, 0, nullptr, false, false, false)
{

}

Instruction::Instruction(uint64_t address, uint64_t size, char *mnemonic, bool isjump, bool iscall, bool isconditional): Block(address, size)
{
    this->setString("mnemonic", (!mnemonic ? "???" : uppercase(mnemonic)));
    this->setBoolean("isjump", isjump);
    this->setBoolean("iscall", iscall);
    this->setBoolean("isconditional", isconditional);
}

Instruction::~Instruction()
{

}

char* Instruction::uppercase(char *s)
{
    char* p = s;

    while(*p)
    {
        *p = toupper(*p);
        p++;
    }

    return s;
}

const char *Instruction::mnemonic() const
{
    return this->getString("mnemonic");
}

bool Instruction::isBranch() const
{
    return this->isJump() || this->isCall();
}

bool Instruction::isJump() const
{
    return this->getInteger("isjump");
}

bool Instruction::isCall() const
{
    return this->getInteger("iscall");
}

bool Instruction::isConditional() const
{
    return this->getInteger("isconditional");
}

bool Instruction::isDestinationValid() const
{
    return this->hasField("destination");
}

uint64_t Instruction::destination() const
{
    return static_cast<uint64_t>(this->getInteger("destination"));
}

Block::Type Instruction::type() const
{
    return Block::InstructionBlock;
}

} // namespace Disassembler
} // namespace PrefLib

