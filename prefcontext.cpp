#include "prefcontext.h"

namespace PrefLib {

PrefContext* PrefContext::_instance = nullptr;

PrefContext::PrefContext(): _logger(&PrefContext::defaultLogger)
{
}

void PrefContext::defaultLogger(PrefContext::LogLevel level, const char *msg, void*)
{
    switch(level)
    {
        case LogLevel::Notice:
            std::cout << "NOTICE: " << msg << std::endl;
            break;

        case LogLevel::Warning:
            std::cout << "WARNING: " << msg << std::endl;
            break;

        case LogLevel::Error:
            std::cout << "ERROR: " << msg << std::endl;
            break;

        default:
            std::cout << msg << std::endl;
            break;
    }
}

PrefContext::~PrefContext()
{
}

void PrefContext::setLogger(PrefContext::LogCallback logger, void *userdata)
{
    this->_logger = logger;
}

PrefContext *PrefContext::instance()
{
    if(!PrefContext::_instance)
        PrefContext::_instance = new PrefContext();

    return PrefContext::_instance;
}

} // namespace PrefLib

