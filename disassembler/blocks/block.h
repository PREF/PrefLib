#ifndef PREFLIB_DISASSEMBLER_BLOCK_H
#define PREFLIB_DISASSEMBLER_BLOCK_H

#include <cstring>
#include "../../core/lua/luax.h"
#include "../../core/lua/luatable.h"

namespace PrefLib {
namespace Disassembler {

using namespace Core::Lua;

class Block : public LuaTable
{
    protected:
        enum Type { InvalidBlock = 0, SegmentBlock = 1, FunctionBlock = 2, LabelBlock = 3, InstructionBlock = 4};

    public:
        Block(uint64_t startaddress, uint64_t size, lua_State* thread = nullptr);
        ~Block();

    public:
        bool isInstructionBlock() const;
        bool isFunctionBlock() const;
        bool isSegmentBlock() const;
        bool isLabelBlock() const;
        bool isEmpty() const;
        bool isCommented() const;
        bool isBookmarked() const;
        bool isRerefenced() const;
        bool contains(uint64_t address);
        uint64_t address() const; /* Syntactic sugar */
        uint64_t startAddress() const;
        uint64_t endAddress() const;
        uint64_t size() const;
        uint8_t weight() const;
        const char* comment() const;
        void setBookmarked(bool b);
        void setReferenced(bool b);
        void setComment(const char* s);

    protected:
        virtual Block::Type type() const = 0;
        virtual int metaIndex(lua_State* l);
        virtual int metaNewIndex(lua_State* l);

    lua_api:
        static int luaMetaIndex(lua_State* l);
        static int luaMetaNewIndex(lua_State* l);

    private:
        bool _bookmarked;
        bool _referenced;
};

} // namespace Disassembler
} // namespace PrefLib

#endif // PREFLIB_DISASSEMBLER_BLOCK_H
