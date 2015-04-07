#include "datatype.h"

namespace PrefLib {

bool DataType::isArithmetic(DataType::Type type)
{
    return type & DataType::Arithmetic;
}

bool DataType::isIntegral(DataType::Type type)
{
    return type & DataType::Integral;
}

bool DataType::isFloatingPoint(DataType::Type type)
{
    return type & DataType::FloatingPoint;
}

bool DataType::isSigned(DataType::Type type)
{
    return DataType::isArithmetic(type) && (type & DataType::Signed);
}

bool DataType::isFloat(DataType::Type type)
{
    return DataType::isFloatingPoint(type) && (DataType::sizeOf(type) == sizeof(float));
}

bool DataType::isDouble(DataType::Type type)
{
    return DataType::isFloatingPoint(type) && (DataType::sizeOf(type) == sizeof(double));
}

bool DataType::isString(DataType::Type type)
{
    return (type & DataType::Vector) && (type & DataType::Characters);
}

bool DataType::isAscii(DataType::Type type)
{
    return DataType::isString(type) && (type & DataType::Ascii);
}

bool DataType::isUnicode(DataType::Type type)
{
    return DataType::isString(type) && (type & DataType::Unicode);
}

bool DataType::isArray(DataType::Type type)
{
    return (type & DataType::Vector);
}

bool DataType::isLittleEndian(DataType::Type type)
{
    return DataType::isArithmetic(type) && (type & DataType::LittleEndian);
}

bool DataType::isBigEndian(DataType::Type type)
{
    return DataType::isArithmetic(type) && (type & DataType::BigEndian);
}

size_t DataType::sizeOf(DataType::Type type)
{
    return DataType::bitWidth(type) / 8;
}

size_t DataType::bitWidth(DataType::Type type)
{
    if(DataType::isArithmetic(type))
        return type & 0xFF;

    if((type == DataType::Blob) || (type == DataType::AsciiCharacter))
        return 8;

    if(type == DataType::UnicodeCharacter)
        return 16;

    return 0;
}

Endianness::Type DataType::endianness(DataType::Type type)
{
    if(DataType::isArithmetic(type))
    {
        if(type & DataType::LittleEndian)
            return Endianness::LittleEndian;

        return Endianness::BigEndian;
    }

    return Endianness::platformEndian();
}

DataType::Type DataType::adjust(DataType::Type type, Endianness::Type endianness)
{
    switch(DataType::bitWidth(type))
    {
        case 16:
            ReturnAdjustType(16);

        case 32:
            ReturnAdjustType(32);

        case 64:
            ReturnAdjustType(64);

        default:
            break;
    }

    return type;
}

DataType::Type DataType::bestType(int bytewidth, bool signedtype)
{
    int bitwidth = bytewidth * 8;

    if(bitwidth <= 8)
        ReturnBestType(signedtype, 8);

    if(bitwidth <= 16)
        ReturnBestType(signedtype, 16);

    if(bitwidth <= 32)
        ReturnBestType(signedtype, 32);

    if(bitwidth <= 64)
        ReturnBestType(signedtype, 64);

    return DataType::Invalid;
}

const char *DataType::stringValue(DataType::Type type)
{
    switch(type)
    {
        case DataType::AsciiCharacter:
            return "AsciiChar";

        case DataType::UnicodeCharacter:
            return "UnicodeChar";

        case DataType::AsciiString:
            return "AsciiString";

        case DataType::UnicodeString:
            return "UnicodeString";

        case DataType::Float:
        case DataType::Float_LE:
        case DataType::Float_BE:
            return "Float";

        case DataType::Double:
        case DataType::Double_LE:
        case DataType::Double_BE:
            return "Double";

        case DataType::Array:
            return "Array";

        case DataType::Blob:
            return "Blob";

        case DataType::UInt8:
            return "UInt8";

        case DataType::UInt16:
        case DataType::UInt16_LE:
        case DataType::UInt16_BE:
            return "UInt16";

        case DataType::UInt32:
        case DataType::UInt32_LE:
        case DataType::UInt32_BE:
            return "UInt32";

        case DataType::UInt64:
        case DataType::UInt64_LE:
        case DataType::UInt64_BE:
            return "UInt64";

        case DataType::Int8:
            return "Int8";

        case DataType::Int16:
        case DataType::Int16_LE:
        case DataType::Int16_BE:
            return "Int16";

        case DataType::Int32:
        case DataType::Int32_LE:
        case DataType::Int32_BE:
            return "Int32";

        case DataType::Int64:
        case DataType::Int64_LE:
        case DataType::Int64_BE:
            return "Int64";

        default:
            break;
    }

    return "Unknown";
}

} // namespace PrefLib

