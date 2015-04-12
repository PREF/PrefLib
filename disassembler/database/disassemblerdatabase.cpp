#include "disassemblerdatabase.h"

namespace PrefLib {
namespace Disassembler {

DisassemblerDatabase::DisassemblerDatabase()
{

}

DisassemblerDatabase::~DisassemblerDatabase()
{

}

bool DisassemblerDatabase::contains(uint64_t address) const
{
    return this->_symbols.find(address) != this->_symbols.end();
}

void DisassemblerDatabase::set(uint64_t address, const char *name)
{
    this->_symbols[address] = name;
}

const char *DisassemblerDatabase::get(uint64_t address)
{    
    return this->_symbols[address];
}

void DisassemblerDatabase::save()
{
}

} // namespace Disassembler
} // namespace PrefLib

