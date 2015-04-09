#include "disassemblerengine.h"

namespace PrefLib {
namespace Disassembler {

DisassemblerEngine::DisassemblerEngine(DisassemblerDefinition *definition): _definition(definition)
{
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

    while(!this->_stack.empty())
    {
        DataValue dv = this->_stack.top();
        dv.castTo(this->_definition->addressType());
        this->_stack.pop();

        if(listing->isDisassembled(dv))
            continue;

        dv = this->_definition->disassemble(listing, dv);

        if(dv.isZero())
            break;

        this->_stack.push(dv);
    }
}

void DisassemblerEngine::prepareStack(DisassemblerListing *listing)
{
    LuaContainer& entrypoints = listing->entryPoints();

    for(size_t i = 0; i < entrypoints.length(); i++)
    {
        Block* b = dynamic_cast<Block*>(entrypoints.getI<LuaTable*>(i));
        this->_stack.push(b->startAddress());
    }
}

} // namespace Disassembler
} // namespace PrefLib

