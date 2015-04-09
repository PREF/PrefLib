#ifndef PREFLIB_DISASSEMBLER_FUNCTION_H
#define PREFLIB_DISASSEMBLER_FUNCTION_H

#include "block.h"

namespace PrefLib {
namespace Disassembler {

class Function : public Block
{
    public:
        enum Type { FunctionBlock = 0x00000000, EntryPointBlock = 0x10000000, ExportBlock = 0x00001000, ImportBlock = 0x00002000 };

    public:
        Function(const char* name, Function::Type functiontype, uint64_t address);
        ~Function();

    public:
        bool isFunction() const;
        bool isEntryPoint() const;
        bool isExport() const;
        bool isImport() const;

    protected:
        virtual Block::Type type() const;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_FUNCTION_H
