#ifndef PREFLIB_DATATYPE_H
#define PREFLIB_DATATYPE_H

#include <cstring>
#include "endianness.h"

#define ReturnAdjustType(w) { if(DataType::isSigned(type)) { \
                                if(endianness == Endianness::LittleEndian) \
                                    return DataType::Int ## w ## _LE; \
                                return DataType::Int ## w ## _BE; \
                              } \
                              if(endianness == Endianness::LittleEndian) \
                                return DataType::UInt ## w ## _LE; \
                              return DataType::UInt ## w ## _BE; }

#define ReturnBestType(signedtype, w) { if(signedtype) \
                                            return DataType::Int ## w; \
                                        return DataType::UInt ## w; }

namespace PrefLib {

class DataType
{
    private:
        enum TypeDefinitions
        {
            Undefined      = 0x00000000,

            Arithmetic     = 0x10000000,
            Characters     = 0x20000000,
            Vector         = 0x40000000,

            Unsigned       = 0x01000000,
            Signed         = 0x02000000,
            Integral       = 0x04000000,
            FloatingPoint  = 0x08000000,

            Ascii          = 0x01000000,
            Unicode        = 0x02000000,

            PlatformEndian = 0x00100000,
            LittleEndian   = 0x00200000,
            BigEndian      = 0x00400000,
        };

    public:
        enum Type
        {
            Invalid          = DataType::Undefined,

            // Platform Dependent Integers
            UInt8            = DataType::PlatformEndian | DataType::Arithmetic | DataType::Integral | DataType::Unsigned | 0x00000008,
            UInt16           = DataType::PlatformEndian | DataType::Arithmetic | DataType::Integral | DataType::Unsigned | 0x00000010,
            UInt32           = DataType::PlatformEndian | DataType::Arithmetic | DataType::Integral | DataType::Unsigned | 0x00000020,
            UInt64           = DataType::PlatformEndian | DataType::Arithmetic | DataType::Integral | DataType::Unsigned | 0x00000040,
            Int8             = DataType::PlatformEndian | DataType::Arithmetic | DataType::Integral | DataType::Signed | 0x00000008,
            Int16            = DataType::PlatformEndian | DataType::Arithmetic | DataType::Integral | DataType::Signed | 0x00000010,
            Int32            = DataType::PlatformEndian | DataType::Arithmetic | DataType::Integral | DataType::Signed | 0x00000020,
            Int64            = DataType::PlatformEndian | DataType::Arithmetic | DataType::Integral | DataType::Signed | 0x00000040,
            Float            = DataType::PlatformEndian | DataType::Arithmetic | DataType::FloatingPoint | DataType::Signed | 0x00000020,
            Double           = DataType::PlatformEndian | DataType::Arithmetic | DataType::FloatingPoint | DataType::Signed | 0x00000040,

            // Little Endian Integers
            UInt16_LE        = DataType::LittleEndian | DataType::Arithmetic | DataType::Integral | DataType::Unsigned | 0x00000010,
            UInt32_LE        = DataType::LittleEndian | DataType::Arithmetic | DataType::Integral | DataType::Unsigned | 0x00000020,
            UInt64_LE        = DataType::LittleEndian | DataType::Arithmetic | DataType::Integral | DataType::Unsigned | 0x00000040,
            Int16_LE         = DataType::LittleEndian | DataType::Arithmetic | DataType::Integral | DataType::Signed | 0x00000010,
            Int32_LE         = DataType::LittleEndian | DataType::Arithmetic | DataType::Integral | DataType::Signed | 0x00000020,
            Int64_LE         = DataType::LittleEndian | DataType::Arithmetic | DataType::Integral | DataType::Signed | 0x00000040,
            Float_LE         = DataType::LittleEndian | DataType::Arithmetic | DataType::FloatingPoint | DataType::Signed | 0x00000020,
            Double_LE        = DataType::LittleEndian | DataType::Arithmetic | DataType::FloatingPoint | DataType::Signed | 0x00000040,

            // Big Endian Integers
            UInt16_BE        = DataType::BigEndian | DataType::Arithmetic | DataType::Integral | DataType::Unsigned | 0x00000010,
            UInt32_BE        = DataType::BigEndian | DataType::Arithmetic | DataType::Integral | DataType::Unsigned | 0x00000020,
            UInt64_BE        = DataType::BigEndian | DataType::Arithmetic | DataType::Integral | DataType::Unsigned | 0x00000040,
            Int16_BE         = DataType::BigEndian | DataType::Arithmetic | DataType::Integral | DataType::Signed | 0x00000010,
            Int32_BE         = DataType::BigEndian | DataType::Arithmetic | DataType::Integral | DataType::Signed | 0x00000020,
            Int64_BE         = DataType::BigEndian | DataType::Arithmetic | DataType::Integral | DataType::Signed | 0x00000040,
            Float_BE         = DataType::BigEndian | DataType::Arithmetic | DataType::FloatingPoint | DataType::Signed | 0x00000020,
            Double_BE        = DataType::BigEndian | DataType::Arithmetic | DataType::FloatingPoint | DataType::Signed | 0x00000040,

            // Characters & Strings
            AsciiCharacter   = DataType::Characters | DataType::Ascii,
            UnicodeCharacter = DataType::Characters | DataType::Unicode,
            Character        = DataType::AsciiCharacter,

            Array            = DataType::Vector,
            AsciiString      = DataType::Vector | DataType::Characters | DataType::Ascii,
            UnicodeString    = DataType::Vector | DataType::Characters | DataType::Unicode,

            Blob             = DataType::Undefined,
        };

    public:
        static bool isArithmetic(DataType::Type type);
        static bool isIntegral(DataType::Type type);
        static bool isFloatingPoint(DataType::Type type);
        static bool isSigned(DataType::Type type);
        static bool isFloat(DataType::Type type);
        static bool isDouble(DataType::Type type);
        static bool isString(DataType::Type type);
        static bool isAscii(DataType::Type type);
        static bool isUnicode(DataType::Type type);
        static bool isArray(DataType::Type type);
        static bool isLittleEndian(DataType::Type type);
        static bool isBigEndian(DataType::Type type);
        static size_t sizeOf(DataType::Type type);
        static size_t bitWidth(DataType::Type type);
        static Endianness::Type endianness(DataType::Type type);
        static DataType::Type adjust(DataType::Type type, Endianness::Type endianness);
        static DataType::Type bestType(int bytewidth, bool signedtype);
        static const char* stringValue(DataType::Type type);
};

} // namespace PrefLib

#endif // PREFLIB_DATATYPE_H
