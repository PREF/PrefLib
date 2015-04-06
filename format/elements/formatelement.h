#ifndef PREFLIB_FORMAT_FORMATELEMENT_H
#define PREFLIB_FORMAT_FORMATELEMENT_H

#include <cstdint>
#include <cstring>
#include "core/luatable.h"
#include "../../io/databuffer.h"

namespace PrefLib {
namespace Format {

using namespace Core;

class FormatTree;

class ValuedField
{
    public:
        virtual DataValue value() = 0;
};

class FormatElement: public Core::LuaTable
{
    protected:
        enum Type { InvalidType, StructureType, FieldType, FieldArrayType, BitFieldType };

    public:
        typedef const char* (*FieldCallback)(FormatElement*);

    private:
        struct Callback
        {
            bool IsLua;
            union { int Lua; FieldCallback Cpp; };
        };

    public:
        FormatElement(FormatTree* formattree, IO::DataBuffer* databuffer, uint64_t offset, const char* name, FormatElement* parent = nullptr);
        ~FormatElement();
        bool isDynamic() const;
        bool isStructure() const;
        bool isField() const;
        bool isFieldArray() const;
        bool isBitField() const;
        virtual uint64_t size() = 0;
        uint64_t offset() const;
        uint64_t endOffset();
        uint64_t base() const;
        const char* info();
        const char* name() const;
        FormatTree* tree() const;
        FormatElement* parent() const;
        virtual void setBase(uint64_t base);
        void setInfoProvider(FieldCallback infocallback);
        void setDynamic(FieldCallback dynamiccallback);
        void populate();

    lua_api:
        static int luaInfoProvider(lua_State* l);
        static int luaDynamic(lua_State* l);
        static int luaMetaIndex(lua_State* l);
        static int luaMetaNewIndex(lua_State* l);
        static int luaMetaLength(lua_State* l);

    protected:
        IO::DataBuffer* dataBuffer() const;
        virtual FormatElement::Type type() const = 0;
        virtual int metaIndex(lua_State* l);
        virtual int metaNewIndex(lua_State* l);
        int metaLength(lua_State* l);
        virtual bool parseDynamic(const char **errmsg = nullptr);

    protected:
        IO::DataBuffer* _databuffer;
        bool _dynamic;

    private:
        uint64_t _base;
        Callback _infocallback;
        Callback _dynamiccallback;
};

} // namespace Format
} // namespace PrefLib

#endif // PREFLIB_FORMAT_FORMATELEMENT_H
