#include "endianness.h"

namespace PrefLib {

const Endianness::PlatformEndianU Endianness::_platformendian = { {0x00, 0x01, 0x02, 0x03} };

Endianness::Type Endianness::platformEndian()
{
    return static_cast<Endianness::Type>(Endianness::_platformendian.value);
}

void Endianness::swapEndianness(int16_t* val)
{
    Endianness::swapEndianness(reinterpret_cast<uint16_t*>(val));
}

void Endianness::swapEndianness(int32_t* val)
{
    Endianness::swapEndianness(reinterpret_cast<uint32_t*>(val));
}

void Endianness::swapEndianness(int64_t* val)
{
    Endianness::swapEndianness(reinterpret_cast<uint64_t*>(val));
}

void Endianness::swapEndianness(uint16_t* val)
{
    unsigned char b1 = *val & 0xFF, b2 = (*val >> 8u) & 0xFF;
    *val = (b1 << 8u) + b2;
}

void Endianness::swapEndianness(uint32_t* val)
{
    unsigned char b1 = *val & 0xFF, b2 = (*val >> 8u) & 0xFF,
                  b3 = (*val >> 16u) & 0xFF, b4 = (*val >> 24u) & 0xFF;

     *val = (static_cast<uint32_t>(b1) << 24u) + (static_cast<uint32_t>(b2) << 16u) + (static_cast<uint32_t>(b3) << 8u) + b4;
}

void Endianness::swapEndianness(uint64_t* val)
{
    unsigned char b1 = *val & 0xFF, b2 = (*val >> 8u) & 0xFF, b3 = (*val >> 16u) & 0xFF, b4 = (*val >> 24u) & 0xFF,
                  b5 = (*val >> 32u) & 0xFF, b6 = (*val >> 40u) & 0xFF, b7 = (*val >> 48u) & 0xFF, b8 = (*val >> 56u) & 0xFF;

     *val = (static_cast<uint64_t>(b1) << 56u) + (static_cast<uint64_t>(b2) << 48u) + (static_cast<uint64_t>(b3) << 40u) + (static_cast<uint64_t>(b4) << 32u) +
            (static_cast<uint64_t>(b5) << 24u) + (static_cast<uint64_t>(b6) << 16u) + (static_cast<uint64_t>(b7) << 8u) + b8;
}

} // namespace PrefLib

