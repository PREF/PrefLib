#include "instruction.h"

namespace PrefLib {
namespace Disassembler {

Instruction::Instruction(uint64_t address): Instruction(address, 0, "???", false, false, false)
{

}

Instruction::Instruction(uint64_t address, uint64_t size, const char *mnemonic, bool isjump, bool iscall, bool isconditional): Block(address, size)
{
    lua_State* l = LuaState::instance();

    this->push();
    this->setString("mnemonic", mnemonic);
    this->setBoolean("isjump", isjump);
    this->setBoolean("iscall", iscall);
    this->setBoolean("isconditional", isconditional);
    lua_pop(l, 1);
}

Instruction::~Instruction()
{

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

