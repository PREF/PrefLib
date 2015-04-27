#include "disassemblerdatabase.h"

namespace PrefLib {
namespace Disassembler {

DisassemblerDatabase::DisassemblerDatabase()
{

}

DisassemblerDatabase::~DisassemblerDatabase()
{
    std::list<const char*>::iterator it = this->_symbollist.begin();

    for(; it != this->_symbollist.end(); it++)
        delete[] *it;

    this->_symbollist.clear();
    this->_symbols.clear();
}

bool DisassemblerDatabase::contains(uint64_t address) const
{
    return this->_symbols.find(address) != this->_symbols.end();
}

void DisassemblerDatabase::set(uint64_t address, const char *name)
{
    char* copiedname = strdup(name); // Keep an internal copy

    this->_symbols[address] = copiedname;
    this->_symbollist.push_back(copiedname);
}

void DisassemblerDatabase::setVariable(uint64_t address, DataType::Type type, const char *name)
{
    if(!this->contains(address))
        this->_variables.push_back(Variable(address, type));

    this->set(address, name);
}

void DisassemblerDatabase::setString(uint64_t address)
{
    this->_strings.push_back(address);
}

const char *DisassemblerDatabase::get(uint64_t address) const
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

