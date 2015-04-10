#include "disassemblerengine.h"

namespace PrefLib {
namespace Disassembler {

DisassemblerEngine::DisassemblerEngine(DisassemblerDefinition *definition): LuaTable(), _definition(definition)
{
    lua_State* l = LuaState::instance();

    this->push();
    this->setFunction("next", &DisassemblerEngine::luaNext);
    this->setFunction("enqueue", &DisassemblerEngine::luaEnqueue);
    lua_pop(l, 1);

    definition->initialize();
}

DisassemblerEngine::~DisassemblerEngine()
{
    this->_definition->finalize();
}

void DisassemblerEngine::disassemble(DisassemblerListing *listing)
{
    this->_definition->map(listing);
    this->prepareStack(listing);

    while(!this->_queue.empty())
    {
        DataValue dv = this->_queue.front();
        dv.castTo(this->_definition->addressType());
        this->_queue.pop_front();

        if(listing->isDisassembled(dv))
            continue;

        dv = this->_definition->disassemble(this, listing, dv);

        if(dv.isZero()) /* if return 0 then stop */
            break;
    }
}

void DisassemblerEngine::prepareStack(DisassemblerListing *listing)
{
    LuaContainer& entrypoints = listing->entryPoints();

    for(size_t i = 0; i < entrypoints.length(); i++)
    {
        Block* b = dynamic_cast<Block*>(entrypoints.getI<LuaTable*>(i));
        this->_queue.push_back(b->startAddress());
    }
}

int DisassemblerEngine::luaNext(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 2);

    DisassemblerEngine* engine = reinterpret_cast<DisassemblerEngine*>(checkThis(l, 1));
    int t = lua_type(l, 2);

    if(t == LUA_TTABLE) /* Custom Instruction */
    {
        Block* b = reinterpret_cast<Block*>(checkThis(l, 2));
        engine->_queue.push_front(b->address() + b->size());
        return 0;
    }

    cs_insn* insn = (*(cs_insn**)luaL_checkudata(l, 2, "cs_insn"));
    engine->_queue.push_front(insn->address + insn->size);
    return 0;
}

int DisassemblerEngine::luaEnqueue(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 2);

    DisassemblerEngine* engine = reinterpret_cast<DisassemblerEngine*>(checkThis(l, 1));
    DataValue address = luaL_checkinteger(l, 2);

    address.castTo(engine->_definition->addressType());
    engine->_queue.push_back(address);
    return 0;
}

} // namespace Disassembler
} // namespace PrefLib

