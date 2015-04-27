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
        typedef std::pair<uint64_t, DataType::Type> Variable;

    public:
        typedef std::map<uint64_t, const char*> SymbolMap;
        typedef std::deque<Variable> VariableList;
        typedef std::deque<uint64_t> StringList;

    public:
        DisassemblerDatabase();
        ~DisassemblerDatabase();
        bool contains(uint64_t address) const;
        void set(uint64_t address, const char* name);
        void setVariable(uint64_t address, DataType::Type type, const char* name);
        void setString(uint64_t address);
        const char* get(uint64_t address) const;
        const VariableList& variables() const;
        const StringList& strings() const;

    public:
        void save();

    private:
        SymbolMap _symbols;
        VariableList _variables;
        StringList _strings;
        std::list<const char*> _symbollist;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_DISASSEMBLERDATABASE_H
