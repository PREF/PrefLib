#include "prefexception.h"

namespace PrefLib {

PrefException::PrefException(const char* msg): _msg(msg)
{

}

PrefException::~PrefException()
{

}

const char *PrefException::what() const _GLIBCXX_USE_NOEXCEPT
{
    return this->_msg;
}

} // namespace PrefLib

