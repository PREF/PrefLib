#include "datatype.h"

namespace PrefLib {

void DataType::pushTable(lua_State *l)
{
    lua_newtable(l);

    /* Fields */
    lua_pushinteger(l, DataType::Invalid);
    lua_setfield(l, -2, "Invalid");

    lua_pushinteger(l, DataType::UInt8);
    lua_setfield(l, -2, "UInt8");
    lua_pushinteger(l, DataType::UInt16);
    lua_setfield(l, -2, "UInt16");
    lua_pushinteger(l, DataType::UInt32);
    lua_setfield(l, -2, "UInt32");
    lua_pushinteger(l, DataType::UInt64);
    lua_setfield(l, -2, "UInt64");

    lua_pushinteger(l, DataType::Int8);
    lua_setfield(l, -2, "Int8");
    lua_pushinteger(l, DataType::Int16);
    lua_setfield(l, -2, "Int16");
    lua_pushinteger(l, DataType::Int32);
    lua_setfield(l, -2, "Int32");
    lua_pushinteger(l, DataType::Int64);
    lua_setfield(l, -2, "Int64");

    lua_pushinteger(l, DataType::Float);
    lua_setfield(l, -2, "Float");
    lua_pushinteger(l, DataType::Double);
    lua_setfield(l, -2, "Double");

    lua_pushinteger(l, DataType::UInt16_LE);
    lua_setfield(l, -2, "UInt16_LE");
    lua_pushinteger(l, DataType::UInt32_LE);
    lua_setfield(l, -2, "UInt32_LE");
    lua_pushinteger(l, DataType::UInt64_LE);
    lua_setfield(l, -2, "UInt64_LE");

    lua_pushinteger(l, DataType::Int16_LE);
    lua_setfield(l, -2, "Int16_LE");
    lua_pushinteger(l, DataType::Int32_LE);
    lua_setfield(l, -2, "Int32_LE");
    lua_pushinteger(l, DataType::Int64_LE);
    lua_setfield(l, -2, "Int64_LE");

    lua_pushinteger(l, DataType::Float_LE);
    lua_setfield(l, -2, "Float_LE");
    lua_pushinteger(l, DataType::Double_LE);
    lua_setfield(l, -2, "Double_LE");

    lua_pushinteger(l, DataType::UInt16_BE);
    lua_setfield(l, -2, "UInt16_BE");
    lua_pushinteger(l, DataType::UInt32_BE);
    lua_setfield(l, -2, "UInt32_BE");
    lua_pushinteger(l, DataType::UInt64_BE);
    lua_setfield(l, -2, "UInt64_BE");

    lua_pushinteger(l, DataType::Int16_BE);
    lua_setfield(l, -2, "Int16_BE");
    lua_pushinteger(l, DataType::Int32_BE);
    lua_setfield(l, -2, "Int32_BE");
    lua_pushinteger(l, DataType::Int64_BE);
    lua_setfield(l, -2, "Int64_BE");

    lua_pushinteger(l, DataType::Float_BE);
    lua_setfield(l, -2, "Float_BE");
    lua_pushinteger(l, DataType::Double_BE);
    lua_setfield(l, -2, "Double_BE");

    lua_pushinteger(l, DataType::AsciiCharacter);
    lua_setfield(l, -2, "AsciiCharacter");
    lua_pushinteger(l, DataType::UnicodeCharacter);
    lua_setfield(l, -2, "UnicodeCharacter");
    lua_pushinteger(l, DataType::Character);
    lua_setfield(l, -2, "Character");

    lua_pushinteger(l, DataType::Array);
    lua_setfield(l, -2, "Array");
    lua_pushinteger(l, DataType::AsciiString);
    lua_setfield(l, -2, "AsciiString");
    lua_pushinteger(l, DataType::UnicodeString);
    lua_setfield(l, -2, "UnicodeString");

    lua_pushinteger(l, DataType::Blob);
    lua_setfield(l, -2, "Blob");


    /* Functions */
    lua_pushcfunction(l, &DataType::luaIsArithmetic);
    lua_setfield(l, -2, "isarithmetic");

    lua_pushcfunction(l, &DataType::luaIsIntegral);
    lua_setfield(l, -2, "isintegral");

    lua_pushcfunction(l, &DataType::luaIsFloatingPoint);
    lua_setfield(l, -2, "isfloatingpoint");

    lua_pushcfunction(l, &DataType::luaIsSigned);
    lua_setfield(l, -2, "issigned");

    lua_pushcfunction(l, &DataType::luaIsFloat);
    lua_setfield(l, -2, "isfloat");

    lua_pushcfunction(l, &DataType::luaIsDouble);
    lua_setfield(l, -2, "isdouble");

    lua_pushcfunction(l, &DataType::luaIsString);
    lua_setfield(l, -2, "isstring");

    lua_pushcfunction(l, &DataType::luaIsAscii);
    lua_setfield(l, -2, "isascii");

    lua_pushcfunction(l, &DataType::luaIsUnicode);
    lua_setfield(l, -2, "isunicode");

    lua_pushcfunction(l, &DataType::luaIsArray);
    lua_setfield(l, -2, "isarray");

    lua_pushcfunction(l, &DataType::luaIsLittleEndian);
    lua_setfield(l, -2, "islittleendian");

    lua_pushcfunction(l, &DataType::luaIsBigEndian);
    lua_setfield(l, -2, "isbigendian");

    lua_pushcfunction(l, &DataType::luaSizeOf);
    lua_setfield(l, -2, "sizeof");

    lua_pushcfunction(l, &DataType::luaBitWidth);
    lua_setfield(l, -2, "bitwidth");

    lua_pushcfunction(l, &DataType::luaEndianness);
    lua_setfield(l, -2, "endianness");

    lua_pushcfunction(l, &DataType::luaAdjust);
    lua_setfield(l, -2, "adjust");

    lua_pushcfunction(l, &DataType::luaBestType);
    lua_setfield(l, -2, "besttype");

    lua_pushcfunction(l, &DataType::luaStringValue);
    lua_setfield(l, -2, "stringvalue");
}

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
        if(type & DataType::PlatformEndian)
            return Endianness::platformEndian();

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

int DataType::luaIsArithmetic(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    lua_pushinteger(l, DataType::isArithmetic(static_cast<DataType::Type>(luaL_checkinteger(l, 1))));
    return 1;
}

int DataType::luaIsIntegral(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    lua_pushinteger(l, DataType::isIntegral(static_cast<DataType::Type>(luaL_checkinteger(l, 1))));
    return 1;
}

int DataType::luaIsFloatingPoint(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    lua_pushinteger(l, DataType::isFloatingPoint(static_cast<DataType::Type>(luaL_checkinteger(l, 1))));
    return 1;
}

int DataType::luaIsSigned(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    lua_pushinteger(l, DataType::isSigned(static_cast<DataType::Type>(luaL_checkinteger(l, 1))));
    return 1;
}

int DataType::luaIsFloat(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    lua_pushinteger(l, DataType::isFloat(static_cast<DataType::Type>(luaL_checkinteger(l, 1))));
    return 1;
}

int DataType::luaIsDouble(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    lua_pushinteger(l, DataType::isDouble(static_cast<DataType::Type>(luaL_checkinteger(l, 1))));
    return 1;
}

int DataType::luaIsString(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    lua_pushinteger(l, DataType::isString(static_cast<DataType::Type>(luaL_checkinteger(l, 1))));
    return 1;
}

int DataType::luaIsAscii(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    lua_pushinteger(l, DataType::isAscii(static_cast<DataType::Type>(luaL_checkinteger(l, 1))));
    return 1;
}

int DataType::luaIsUnicode(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    lua_pushinteger(l, DataType::isUnicode(static_cast<DataType::Type>(luaL_checkinteger(l, 1))));
    return 1;
}

int DataType::luaIsArray(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    lua_pushinteger(l, DataType::isArray(static_cast<DataType::Type>(luaL_checkinteger(l, 1))));
    return 1;
}

int DataType::luaIsLittleEndian(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    lua_pushinteger(l, DataType::isLittleEndian(static_cast<DataType::Type>(luaL_checkinteger(l, 1))));
    return 1;
}

int DataType::luaIsBigEndian(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    lua_pushinteger(l, DataType::isBigEndian(static_cast<DataType::Type>(luaL_checkinteger(l, 1))));
    return 1;
}

int DataType::luaSizeOf(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    lua_pushinteger(l, DataType::sizeOf(static_cast<DataType::Type>(luaL_checkinteger(l, 1))));
    return 1;
}

int DataType::luaBitWidth(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    lua_pushinteger(l, DataType::bitWidth(static_cast<DataType::Type>(luaL_checkinteger(l, 1))));
    return 1;
}

int DataType::luaEndianness(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    lua_pushinteger(l, DataType::endianness(static_cast<DataType::Type>(luaL_checkinteger(l, 1))));
    return 1;
}

int DataType::luaAdjust(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 2);

    lua_pushinteger(l, DataType::adjust(static_cast<DataType::Type>(luaL_checkinteger(l, 1)), static_cast<Endianness::Type>(luaL_checkinteger(l, 2))));
    return 1;
}

int DataType::luaBestType(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectminargc(l, argc, 1);

    lua_pushinteger(l, DataType::bestType(static_cast<DataType::Type>(luaL_checkinteger(l, 1)), luaL_optinteger(l, 2, true)));
    return 1;
}

int DataType::luaStringValue(lua_State *l)
{
    int argc = lua_gettop(l);
    luaX_expectargc(l, argc, 1);

    lua_pushstring(l, DataType::stringValue(static_cast<DataType::Type>(luaL_checkinteger(l, 1))));
    return 1;
}

} // namespace PrefLib

