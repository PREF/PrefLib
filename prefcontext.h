#ifndef PREFLIB_PREFCONTEXT_H
#define PREFLIB_PREFCONTEXT_H

#include "io/databuffer.h"

namespace PrefLib {

class PrefContext
{
    public:
        enum LogLevel { Normal, NormalLine, Notice, Warning, Error };
        typedef void (*LogCallback)(LogLevel level, const char* msg, void* userdata);

    private:
        PrefContext();
        static void defaultLogger(LogLevel level, const char* msg, void*);

    public:
        ~PrefContext();
        void setLogger(LogCallback logger, void* userdata = nullptr);
        BTEntryList executeFormat(IO::DataBuffer* databuffer, const std::string& file);
        VMValuePtr inspect(IO::DataBuffer* databuffer);

    public:
        static PrefContext* instance();

    private:
        static PrefContext* _instance;
        LogCallback _logger;
};

} // namespace PrefLib

#endif // PREFLIB_PREFCONTEXT_H
