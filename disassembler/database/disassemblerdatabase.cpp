#include "disassemblerdatabase.h"

namespace PrefLib {
namespace Disassembler {

DisassemblerDatabase::DisassemblerDatabase()
{

}

DisassemblerDatabase::~DisassemblerDatabase()
{
    SymbolMap::iterator it = this->_symbols.begin();

    for(; it != this->_symbols.end(); it++)
    {
        delete[] it->second->Name; // Free allocated string
        delete it->second; // Free Symbol
    }

    this->_symbols.clear();
    this->_variables.clear();
    this->_strings.clear();
}

bool DisassemblerDatabase::contains(uint64_t address) const
{
    return this->_symbols.find(address) != this->_symbols.end();
}

void DisassemblerDatabase::set(uint64_t address, const char *name)
{
    Symbol* symbol = nullptr;

    if(this->contains(address))
    {
        symbol = this->_symbols[address];
        delete[] symbol->Name;
    }
    else
    {
        symbol = new Symbol();
        symbol->Address = address;
        symbol->Type = DataType::Invalid;
        symbol->IsVariable = false;
        symbol->IsString = false;

        this->_symbols[address] = symbol;
    }

    symbol->Name = strdup(name);
}

void DisassemblerDatabase::setVariable(uint64_t address, DataType::Type type, const char *name)
{
    this->set(address, name);
    Symbol* symbol = this->_symbols[address];

    if(symbol->IsVariable)
        return;

    symbol->Type = type;
    symbol->IsVariable = true;
    this->_variables.push_back(symbol);
}

void DisassemblerDatabase::setString(uint64_t address)
{
    Symbol* symbol = this->_symbols[address];

    if(symbol->IsString)
        return;

    symbol->IsString = true;
    this->_strings.push_back(address);
}

const DisassemblerDatabase::Symbol *DisassemblerDatabase::get(uint64_t address) const
{    
    return this->_symbols.at(address);
}

const DisassemblerDatabase::VariableList &DisassemblerDatabase::variables() const
{
    return this->_variables;
}

const DisassemblerDatabase::StringList &DisassemblerDatabase::strings() const
{
    return this->_strings;
}

void DisassemblerDatabase::save()
{
}

} // namespace Disassembler
} // namespace PrefLib

