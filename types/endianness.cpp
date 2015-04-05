#include "endianness.h"

namespace PrefLib {

const Endianness::PlatformEndianU Endianness::_platformendian = { {0, 1, 2, 3} };

Endianness::Type Endianness::platformEndian()
{
    return static_cast<Endianness::Type>(Endianness::_platformendian.value);
}

} // namespace PrefLib

