#include "function.h"

namespace PrefLib {
namespace Disassembler {

Function::Function(Function::Type functiontype, uint64_t address): Block(address, 0)
{
    this->setInteger("type", functiontype);
}

Function::~Function()
{

}

bool Function::isFunction() const
{
    return this->getInteger("type") == Function::FunctionBlock;
}

bool Function::isEntryPoint() const
{
    return this->getInteger("type") == Function::EntryPointBlock;
}

bool Function::isExport() const
{
    return this->getInteger("type") == Function::ExportBlock;
}

bool Function::isImport() const
{
    return this->getInteger("type") == Function::ImportBlock;
}

Block::Type Function::type() const
{
    return Block::FunctionBlock;
}

} // namespace Disassembler
} // namespace PrefLib

