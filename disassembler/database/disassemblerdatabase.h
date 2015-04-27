#ifndef PREFLIB_DISASSEMBLER_DISASSEMBLERDATABASE_H
#define PREFLIB_DISASSEMBLER_DISASSEMBLERDATABASE_H

#define DATABASE_EXTENSION "db"

#include <map>
#include <deque>
#include <list>
#include <cstring>
#include "../../types/datatype.h"

namespace PrefLib {
namespace Disassembler {

class DisassemblerDatabase
{
    public:
        struct Symbol
        {
            uint64_t Address;
            const char* Name;
            DataType::Type Type;
            bool IsVariable;
            bool IsString;
        };

    public:
        typedef std::map<uint64_t, Symbol*> SymbolMap;
        typedef std::deque<Symbol*> VariableList;
        typedef std::deque<uint64_t> StringList;

    public:
        DisassemblerDatabase();
        ~DisassemblerDatabase();
        bool contains(uint64_t address) const;
        void set(uint64_t address, const char* name);
        void setVariable(uint64_t address, DataType::Type type, const char* name);
        void setString(uint64_t address);
        const Symbol* get(uint64_t address) const;
        const VariableList& variables() const;
        const StringList& strings() const;

    public:
        void save();

    private:
        SymbolMap _symbols;
        VariableList _variables;
        StringList _strings;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_DISASSEMBLERDATABASE_H
