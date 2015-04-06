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
#include "core/luax.h"
#include "core/luatable.h"

namespace PrefLib {

class DataValue: public Core::LuaReference
{
    private:
        enum InternalType { Invalid, Integer, Real, String };

        struct UserData
        {
            InternalType Type;
            Endianness::Type Endian;
            bool IsOverflowed;
            bool IsSigned;
            char* StringBuffer;

            union
            {
                int8_t Int8; uint8_t UInt8;
                int16_t Int16; uint16_t UInt16;
                int32_t Int32; uint32_t UInt32;
                int64_t Int64; uint64_t UInt64;
                double Real;
                char* AsciiString;
            } Value;
        };

    lua_api:
        static int luaMetaGc(lua_State* l);
        static int luaMetaIndex(lua_State* l);
        static int luaMetaNewIndex(lua_State* l);
        static int luaMetaUnm(lua_State* l);
        static int luaMetaAdd(lua_State* l);
        static int luaMetaSub(lua_State* l);
        static int luaMetaMul(lua_State* l);
        static int luaMetaDiv(lua_State* l);
        static int luaMetaMod(lua_State* l);
        static int luaMetaPow(lua_State* l);
        static int luaMetaLen(lua_State* l);
        static int luaMetaEq(lua_State* l);
        static int luaMetaLt(lua_State* l);
        static int luaMetaLe(lua_State* l);

    private:
        void allocateUserData();

    public:
        DataValue();
        DataValue(double d);
        DataValue(const char* ch);
        DataValue(const DataValue& dv);
        virtual void push() const;
        void castTo(DataType::Type type);
        const char* toString(unsigned int base = 10, unsigned int width = 0);
        bool isNull() const;
        bool isZero() const;
        bool isOverflowed() const;

        template<typename T> DataValue(T t, typename std::enable_if< std::is_signed<T>::value>::type* = 0);
        template<typename T> DataValue(T t, typename std::enable_if< std::is_unsigned<T>::value>::type* = 0);

    public:
        ~DataValue();

    public:
        unsigned char* operator &();
        operator const char*();
        operator double();
        operator int8_t();
        operator int16_t();
        operator int32_t();
        operator int64_t();
        operator uint8_t();
        operator uint16_t();
        operator uint32_t();
        operator uint64_t();

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
        UserData* _valuestruct;
};

template<typename T> DataValue::DataValue(T t, typename std::enable_if< std::is_signed<T>::value>::type*)
{
    this->allocateUserData();

    this->_valuestruct->StringBuffer = nullptr;
    this->_valuestruct->Type = InternalType::Integer;
    this->_valuestruct->Endian = Endianness::platformEndian();
    this->_valuestruct->IsOverflowed = false;
    this->_valuestruct->IsSigned = true;
    this->_valuestruct->Value.Int64 = t;
}

template<typename T> DataValue::DataValue(T t, typename std::enable_if< std::is_unsigned<T>::value>::type*)
{
    this->allocateUserData();

    this->_valuestruct->StringBuffer = nullptr;
    this->_valuestruct->Type = InternalType::Integer;
    this->_valuestruct->Endian = Endianness::platformEndian();
    this->_valuestruct->IsOverflowed = false;
    this->_valuestruct->IsSigned = false;
    this->_valuestruct->Value.UInt64 = t;
}

template<typename T> bool DataValue::operator ==(const T& t) const
{
    if(std::is_floating_point<T>::value)
        return this->_valuestruct->Value.Real == static_cast<double>(t);

    if(std::is_signed<T>::value)
        return this->_valuestruct->Value.Int64 == static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        return this->_valuestruct->Value.UInt64 == static_cast<uint64_t>(t);

    return false;
}

template<typename T> bool DataValue::operator !=(const T& t) const
{
    if(std::is_floating_point<T>::value)
        return this->_valuestruct->Value.Real != static_cast<double>(t);

    if(std::is_signed<T>::value)
        return this->_valuestruct->Value.Int64 != static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        return this->_valuestruct->Value.UInt64 != static_cast<uint64_t>(t);

    return false;
}

template<typename T> bool DataValue::operator >(const T& t) const
{
    if(std::is_floating_point<T>::value)
        return this->_valuestruct->Value.Real > static_cast<double>(t);

    if(std::is_signed<T>::value)
        return this->_valuestruct->Value.Int64 > static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        return this->_valuestruct->Value.UInt64 > static_cast<uint64_t>(t);

    return false;
}

template<typename T> bool DataValue::operator <(const T& t) const
{
    if(std::is_floating_point<T>::value)
        return this->_valuestruct->Value.Real < static_cast<double>(t);

    if(std::is_signed<T>::value)
        return this->_valuestruct->Value.Int64 < static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        return this->_valuestruct->Value.UInt64 < static_cast<uint64_t>(t);

    return false;
}

template<typename T> bool DataValue::operator >=(const T& t) const
{
    if(std::is_floating_point<T>::value)
        return this->_valuestruct->Value.Real >= static_cast<double>(t);

    if(std::is_signed<T>::value)
        return this->_valuestruct->Value.Int64 >= static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        return this->_valuestruct->Value.UInt64 >= static_cast<uint64_t>(t);

    return false;
}

template<typename T> bool DataValue::operator <=(const T& t) const
{
    if(std::is_floating_point<T>::value)
        return this->_valuestruct->Value.Real <= static_cast<double>(t);

    if(std::is_signed<T>::value)
        return this->_valuestruct->Value.Int64 <= static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        return this->_valuestruct->Value.UInt64 <= static_cast<uint64_t>(t);

    return false;
}

template<typename T> DataValue DataValue::operator &(const T& t) const
{
    if(this->_valuestruct->Type == InternalType::Invalid)
        return DataValue();

    DataValue result = *this;

    if(std::is_signed<T>::value)
        result._valuestruct->Value.Int64 &= static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        result._valuestruct->Value.UInt64 &= static_cast<uint64_t>(t);

    return result;
}

template<typename T> DataValue DataValue::operator |(const T& t) const
{
    if(this->_valuestruct->Type == InternalType::Invalid)
        return DataValue();

    DataValue result = *this;

    if(std::is_signed<T>::value)
        result._valuestruct->Value.Int64 |= static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        result._valuestruct->Value.UInt64 |= static_cast<uint64_t>(t);

    return result;
}

template<typename T> DataValue DataValue::operator ^(const T& t) const
{
    if(this->_valuestruct->Type == InternalType::Invalid)
        return DataValue();

    DataValue result = *this;

    if(std::is_signed<T>::value)
        result._valuestruct->Value.Int64 ^= static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        result._valuestruct->Value.UInt64 ^= static_cast<uint64_t>(t);

    return result;
}

template<typename T> DataValue DataValue::operator <<(const T& t) const
{
    if(this->_valuestruct->Type == InternalType::Invalid)
        return DataValue();

    DataValue result = *this;

    if(std::is_signed<T>::value)
        result._valuestruct->Value.Int64 <<= static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        result._valuestruct->Value.UInt64 <<= static_cast<uint64_t>(t);

    return result;
}

template<typename T> DataValue DataValue::operator >>(const T& t) const
{
    if(this->_valuestruct->Type == InternalType::Invalid)
        return DataValue();

    DataValue result = *this;

    if(std::is_signed<T>::value)
        result._valuestruct->Value.Int64 >>= static_cast<int64_t>(t);

    if(std::is_unsigned<T>::value)
        result._valuestruct->Value.UInt64 >>= static_cast<uint64_t>(t);

    return result;
}

} // namespace PrefLib

#endif // PREFSDK_DATAVALUE_H
