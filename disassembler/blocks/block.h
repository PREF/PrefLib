#ifndef PREFLIB_DISASSEMBLER_BLOCK_H
#define PREFLIB_DISASSEMBLER_BLOCK_H

#include <cstring>
#include "../../core/luax.h"
#include "../../core/luatable.h"

namespace PrefLib {
namespace Disassembler {

using namespace Core;

class Block : public LuaTable
{
    protected:
        enum Type { InvalidBlock, InstructionBlock, FunctionBlock, SegmentBlock, LabelBlock, SymbolBlock };

    public:
        Block(uint64_t startaddress, uint64_t size);
        ~Block();

    public:
        bool isInstructionBlock() const;
        bool isFunctionBlock() const;
        bool isSegmentBlock() const;
        bool isLabelBlock() const;
        bool isSymbolBlock() const;
        bool isEmpty() const;
        bool isBookmarked() const;
        bool contains(uint64_t address);
        uint64_t startAddress() const;
        uint64_t endAddress() const;
        uint64_t size() const;
        void setBookmarked(bool b);

    protected:
        virtual Block::Type type() const = 0;
        virtual int metaIndex(lua_State* l);
        virtual int metaNewIndex(lua_State* l);

    lua_api:
        static int luaMetaIndex(lua_State* l);
        static int luaMetaNewIndex(lua_State* l);

    private:
        bool _bookmarked;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_BLOCK_H
