#ifndef PREFLIB_EXPORTER_EXPORTERDEFINITION_H
#define PREFLIB_EXPORTER_EXPORTERDEFINITION_H

#include "../core/lua/luax.h"
#include "../core/lua/luatable.h"
#include "../io/databuffer.h"

namespace PrefLib {
namespace Exporter {

using namespace Core;

class ExporterDefinition : public LuaTable
{
    public:
        ExporterDefinition(const char* name, const char* description, const char* author, const char* version);
        ~ExporterDefinition();

    public:
        const char* name() const;
        const char* description() const;
        const char* author() const;
        const char* version() const;
        void dump(IO::DataBuffer* databufferin, IO::DataBuffer* databufferout, uint64_t startoffset = 0, uint64_t endoffset = 0);
};

} // namespace Exporter
} // namespace PrefLib

#endif // PREFLIB_EXPORTER_EXPORTERDEFINITION_H
