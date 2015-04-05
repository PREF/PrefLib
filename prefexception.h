#ifndef PREFLIB_PREFEXCEPTION_H
#define PREFLIB_PREFEXCEPTION_H

#include <exception>

namespace PrefLib {

class PrefException : public std::exception
{
    public:
        PrefException(const char* msg);
        ~PrefException();

    public:
        virtual const char* what() const _GLIBCXX_USE_NOEXCEPT;

    private:
        const char* _msg;
};

} // namespace PrefLib

#endif // PREFLIB_PREFEXCEPTION_H
