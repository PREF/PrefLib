#include "capstoneinstruction.h"

namespace PrefLib {
namespace Disassembler {

CapstoneInstruction::CapstoneInstruction(csh handle, cs_insn *insn, int csinsnref, lua_State *thread): Instruction(insn->address, insn->size, insn->mnemonic, cs_insn_group(handle, insn, CS_GRP_JUMP), cs_insn_group(handle, insn, CS_GRP_CALL), false, thread), _handle(handle), _insn(insn), _csinsinref(csinsnref)
{

}

CapstoneInstruction::~CapstoneInstruction()
{
    if(this->_insn)
    {
        cs_free(this->_insn, 1);
        this->_insn = nullptr;
    }

    if(this->_csinsinref != LUA_REFNIL)
    {
        luaL_unref(LuaState::instance(), LUA_REGISTRYINDEX, this->_csinsinref);
        this->_csinsinref = LUA_REFNIL;
    }
}

int CapstoneInstruction::metaIndex(lua_State *l)
{
    int res = Instruction::metaIndex(l);

    if(!res)
    {
        lua_rawgeti(l, LUA_REGISTRYINDEX, this->_csinsinref); /* Push cs_insn* */
        lua_pushvalue(l, 2);
        lua_gettable(l, -2);

        lua_remove(l, -2); /* Pop cs_insn* */
        return 1;
    }

    return res;
}

} // namespace Disassembler
} // namespace PrefLib

