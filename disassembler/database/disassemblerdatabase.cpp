#include "disassemblerdatabase.h"

namespace PrefLib {
namespace Disassembler {

DisassemblerDatabase::DisassemblerDatabase()
{

}

DisassemblerDatabase::~DisassemblerDatabase()
{

}

void DisassemblerDatabase::set(SymbolType type, uint64_t address, const char *name)
{
    if(this->_symbols.find(type) == this->_symbols.end())
        this->_symbols[type] = SymbolsMap();

    Symbol s;
    s.Type = type;
    s.Address = address;
    s.Length = strlen(name);
    strcpy(s.Name, name);

    this->_symbols[type][address] = s;
}

const Symbol& DisassemblerDatabase::get(SymbolType type, uint64_t address)
{
    /*
    if(this->_symbols.find(type) == this->_symbols.end())


    return this->_symbols[type][address];
    */
}

void DisassemblerDatabase::save()
{
}

} // namespace Disassembler
} // namespace PrefLib

