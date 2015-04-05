#ifndef PREFLIB_CORE_LUAREFERENCE_H
#define PREFLIB_CORE_LUAREFERENCE_H

#include "luastate.h"

namespace PrefLib {
namespace Core {

class LuaReference
{
    public:
        LuaReference();
        LuaReference(const LuaReference& lr);
        virtual ~LuaReference();
        virtual void push() const;

    private:
        void deleteReference();
        int cloneReference(const LuaReference& lr);

    public:
        LuaReference& operator=(const LuaReference& rhs);

    protected:
        int _reference;
};

} // namespace Core
} // namespace PrefLib

#endif // PREFLIB_CORE_LUAREFERENCE_H
