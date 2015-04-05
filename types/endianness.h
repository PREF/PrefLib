#ifndef PREFLIB_ENDIANNESS_H
#define PREFLIB_ENDIANNESS_H

#include <cstdint>

namespace PrefLib {

using namespace std;

class Endianness
{
    private:
        union PlatformEndianU { unsigned char bytes[4]; uint32_t value; };

    public:
        enum Type { LittleEndian = 0x03020100ul, BigEndian = 0x00010203ul /*, PdpEndian = 0x01000302ul */ };

    public:
        static Endianness::Type platformEndian();

    private:
        static const PlatformEndianU _platformendian;
};

} // namespace PrefLib

#endif // PREFLIB_ENDIANNESS_H
