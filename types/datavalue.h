#ifndef PREFSDK_DATAVALUE_H
#define PREFSDK_DATAVALUE_H

#include <cstdint>
#include <cstdio>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <inttypes.h>
#include <type_traits>
#include "datatype.h"
#include "core/lua/luatable.h"

namespace PrefLib {

using namespace Lua;

class DataValue
{
    private:
        enum InternalType { Invalid, Integer, Float, Double, Character, String };

        struct UserData
        {
            InternalType Type;
            Endianness::Type Endian;
            bool IsOverflowed;
            bool IsSigned;
            char* StringBuffer;

            union
            {
                char Character;
                int8_t Int8; uint8_t UInt8;
                int16_t Int16; uint16_t UInt16;
                int32_t Int32; uint32_t UInt32;
                int64_t Int64; uint64_t UInt64;
                float Float;
                double Double;
                char* AsciiString;
            } Value;
        };

    private:
        static bool isArithmetic(InternalType type);

    public:
        DataValue();
        DataValue(float d);
        DataValue(double d);
        DataValue(char ch);
        DataValue(const char* s);
        DataValue(const DataValue& dv);
        virtual void push(lua_State *l) const;
        void castTo(DataType::Type type);
        const char* toString(unsigned int base = 10, unsigned int width = 0);
        Endianness::Type endianness() const;
        bool isNull() const;
        bool isZero() const;
        bool isSigned() const;
        bool isOverflowed() const;
        bool isArithmetic() const;
        bool isIntegral() const;
        bool isFloatingPoint() const;
        bool isString() const;
        bool isCharacter() const;

        template<typename T> DataValue(T t, typename std::enable_if< std::is_signed<T>::value>::type* = 0);
        template<typename T> DataValue(T t, typename std::enable_if< std::is_unsigned<T>::value>::type* = 0);

    public:
        ~DataValue();

    public:
        unsigned char* operator &();
        operator const char*() const;
        operator float() const;
        operator double() const;
        operator int8_t() const;
        operator int16_t() const;
        operator int32_t() const;
        operator int64_t() const;
        operator uint8_t() const;
        operator uint16_t() const;
        operator uint32_t() const;
        operator uint64_t() const;

    public:
        bool operator ==(const char* s) const;
        bool operator !=(const char* s) const;

        bool operator ==(const DataValue &rhs) const;
        bool operator !=(const DataValue &rhs) const;
        bool operator >(const DataValue &rhs) const;
        bool operator <(const DataValue &rhs) const;
        bool operator >=(const DataValue &rhs) const;
        bool operator <=(const DataValue &rhs) const;
        DataValue operator &(const DataValue &rhs) const;
        DataValue operator |(const DataValue &rhs) const;
        DataValue operator ^(const DataValue &rhs) const;
        DataValue operator <<(const DataValue &rhs) const;
        DataValue operator >>(const DataValue &rhs) const;

        template<typename T> bool operator ==(const T& t) const;
        template<typename T> bool operator !=(const T& t) const;
        template<typename T> bool operator >(const T& t) const;
        template<typename T> bool operator <(const T& t) const;
        template<typename T> bool operator >=(const T& t) const;
        template<typename T> bool operator <=(const T& t) const;
        template<typename T> DataValue operator ~() const;
        template<typename T> DataValue operator &(const T& t) const;
        template<typename T> DataValue operator |(const T& t) const;
        template<typename T> DataValue operator ^(const T& t) const;
        template<typename T> DataValue operator <<(const T& t) const;
        template<typename T> DataValue operator >>(const T& t) const;

    public:
        DataValue& operator =(const DataValue &rhs);
        DataValue operator ~() const;
        DataValue& operator ++();
        DataValue& operator --();
        DataValue operator ++(int) const;
        DataValue operator --(int) const;
        DataValue& operator +=(const DataValue &rhs);
        DataValue& operator -=(const DataValue &rhs);
        DataValue operator +(const DataValue &rhs) const;
        DataValue operator -(const DataValue &rhs) const;

    private:
        UserData _valuestruct;
};

template<typename T> DataValue::DataValue(T t, typename std::enable_if< std::is_signed<T>::value>::type*)
{
    this->_valuestruct.StringBuffer = nullptr;
    this->_valuestruct.Type = InternalType::Integer;
    this->_valuestruct.Endian = Endianness::platformEndian();
    this->_valuestruct.IsOverflowed = false;
    this->_valuestruct.IsSigned = true;
    this->_valuestruct.Value.Int64 = t;
}

template<typename T> DataValue::DataValue(T t, typename std::enable_if< std::is_unsigned<T>::value>::type*)
{
    this->_valuestruct.StringBuffer = nullptr;
    this->_valuestruct.Type = InternalType::Integer;
    this->_valuestruct.Endian = Endianness::platformEndian();
    this->_valuestruct.IsOverflowed = false;
    this->_valuestruct.IsSigned = false;
    this->_valuestruct.Value.UInt64 = t;
}

template<typename T> bool DataValue::operator ==(const T& t) const
{
    if(std::is_floating_point<T>::value)
        return this->_valuestruct.Value.Double == static_cast<double>(t);

    if(std::is_signed<T>::value)
        return this->_valuestruct.Value.Int64 == static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        return this->_valuestruct.Value.UInt64 == static_cast<uint64_t>(t);

    return false;
}

template<typename T> bool DataValue::operator !=(const T& t) const
{
    if(std::is_floating_point<T>::value)
        return this->_valuestruct.Value.Double != static_cast<double>(t);

    if(std::is_signed<T>::value)
        return this->_valuestruct.Value.Int64 != static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        return this->_valuestruct.Value.UInt64 != static_cast<uint64_t>(t);

    return false;
}

template<typename T> bool DataValue::operator >(const T& t) const
{
    if(std::is_floating_point<T>::value)
        return this->_valuestruct.Value.Double > static_cast<double>(t);

    if(std::is_signed<T>::value)
        return this->_valuestruct.Value.Int64 > static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        return this->_valuestruct.Value.UInt64 > static_cast<uint64_t>(t);

    return false;
}

template<typename T> bool DataValue::operator <(const T& t) const
{
    if(std::is_floating_point<T>::value)
        return this->_valuestruct.Value.Double < static_cast<double>(t);

    if(std::is_signed<T>::value)
        return this->_valuestruct.Value.Int64 < static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        return this->_valuestruct.Value.UInt64 < static_cast<uint64_t>(t);

    return false;
}

template<typename T> bool DataValue::operator >=(const T& t) const
{
    if(std::is_floating_point<T>::value)
        return this->_valuestruct.Value.Double >= static_cast<double>(t);

    if(std::is_signed<T>::value)
        return this->_valuestruct.Value.Int64 >= static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        return this->_valuestruct.Value.UInt64 >= static_cast<uint64_t>(t);

    return false;
}

template<typename T> bool DataValue::operator <=(const T& t) const
{
    if(std::is_floating_point<T>::value)
        return this->_valuestruct.Value.Double <= static_cast<double>(t);

    if(std::is_signed<T>::value)
        return this->_valuestruct.Value.Int64 <= static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        return this->_valuestruct.Value.UInt64 <= static_cast<uint64_t>(t);

    return false;
}

template<typename T> DataValue DataValue::operator &(const T& t) const
{
    if(this->_valuestruct.Type == InternalType::Invalid)
        return DataValue();

    DataValue result = *this;

    if(std::is_signed<T>::value)
        result._valuestruct.Value.Int64 &= static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        result._valuestruct.Value.UInt64 &= static_cast<uint64_t>(t);

    return result;
}

template<typename T> DataValue DataValue::operator |(const T& t) const
{
    if(this->_valuestruct.Type == InternalType::Invalid)
        return DataValue();

    DataValue result = *this;

    if(std::is_signed<T>::value)
        result._valuestruct.Value.Int64 |= static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        result._valuestruct.Value.UInt64 |= static_cast<uint64_t>(t);

    return result;
}

template<typename T> DataValue DataValue::operator ^(const T& t) const
{
    if(this->_valuestruct.Type == InternalType::Invalid)
        return DataValue();

    DataValue result = *this;

    if(std::is_signed<T>::value)
        result._valuestruct.Value.Int64 ^= static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        result._valuestruct.Value.UInt64 ^= static_cast<uint64_t>(t);

    return result;
}

template<typename T> DataValue DataValue::operator <<(const T& t) const
{
    if(this->_valuestruct.Type == InternalType::Invalid)
        return DataValue();

    DataValue result = *this;

    if(std::is_signed<T>::value)
        result._valuestruct.Value.Int64 <<= static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        result._valuestruct.Value.UInt64 <<= static_cast<uint64_t>(t);

    return result;
}

template<typename T> DataValue DataValue::operator >>(const T& t) const
{
    if(this->_valuestruct.Type == InternalType::Invalid)
        return DataValue();

    DataValue result = *this;

    if(std::is_signed<T>::value)
        result._valuestruct.Value.Int64 >>= static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        result._valuestruct.Value.UInt64 >>= static_cast<uint64_t>(t);

    return result;
}

} // namespace PrefLib

#endif // PREFSDK_DATAVALUE_H
