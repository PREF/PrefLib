#ifndef PREFLIB_DISASSEMBLER_DISASSEMBLERDATABASE_H
#define PREFLIB_DISASSEMBLER_DISASSEMBLERDATABASE_H

#define DATABASE_EXTENSION "db"

#include <map>
#include <cstring>

namespace PrefLib {
namespace Disassembler {

class DisassemblerDatabase
{
    public:
        typedef std::map<uint64_t, const char*> SymbolMap;

    public:
        DisassemblerDatabase();
        ~DisassemblerDatabase();
        bool contains(uint64_t address) const;
        void set(uint64_t address, const char* name);
        const char* get(uint64_t address);

    public:
        void save();

    private:
        SymbolMap _symbols;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_DISASSEMBLERDATABASE_H
