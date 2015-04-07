#ifndef PREFLIB_ENDIANNESS_H
#define PREFLIB_ENDIANNESS_H

#include <cstdint>
#include <type_traits>

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

    public:
        template<typename T> static void swapEndianness(T&) { }
        static void swap(int16_t* val);
        static void swap(int32_t* val);
        static void swap(int64_t* val);
        static void swap(uint16_t* val);
        static void swap(uint32_t* val);
        static void swap(uint64_t* val);
        static void swap(float* val);
        static void swap(double* val);

    private:
        static const PlatformEndianU _platformendian;
};

} // namespace PrefLib

#endif // PREFLIB_ENDIANNESS_H
