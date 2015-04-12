#ifndef PREFLIB_DISASSEMBLER_DISASSEMBLERDATABASE_H
#define PREFLIB_DISASSEMBLER_DISASSEMBLERDATABASE_H

#define DATABASE_EXTENSION "db"

#include <map>
#include "symbol.h"

namespace PrefLib {
namespace Disassembler {

class DisassemblerDatabase
{
    public:
        typedef std::map<uint64_t, Symbol> SymbolsMap;
        typedef std::map<SymbolType, SymbolsMap> SymbolTypeMap;

    public:
        DisassemblerDatabase();
        ~DisassemblerDatabase();
        void set(SymbolType type, uint64_t address, const char* name);
        const Symbol &get(SymbolType type, uint64_t address);

    public:
        void save();

    private:
        SymbolTypeMap _symbols;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_DISASSEMBLERDATABASE_H
