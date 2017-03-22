#ifndef PREFLIB_PREFCONTEXT_H
#define PREFLIB_PREFCONTEXT_H

#include <iostream>
#include "support/algorithm.h"

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

    public:
        static PrefContext* instance();

    private:
        static PrefContext* _instance;
        LogCallback _logger;
};

} // namespace PrefLib

#endif // PREFLIB_PREFCONTEXT_H
