#include "datavalue.h"

namespace PrefLib {

bool DataValue::isArithmetic(DataValue::InternalType type)
{
    return (type == InternalType::Integer) || (type == InternalType::Float) || (type == InternalType::Double);
}

DataValue::DataValue()
{
    this->_valuestruct.Endian = Endianness::platformEndian();
    this->_valuestruct.IsOverflowed = false;
    this->_valuestruct.IsSigned = false;
    this->_valuestruct.StringBuffer = nullptr;
    this->_valuestruct.Type = InternalType::Invalid;
    this->_valuestruct.Value.UInt64 = 0u;
}

DataValue::DataValue(float f)
{
    this->_valuestruct.Endian = Endianness::platformEndian();
    this->_valuestruct.IsOverflowed = false;
    this->_valuestruct.IsSigned = true;
    this->_valuestruct.StringBuffer = nullptr;
    this->_valuestruct.Type = InternalType::Float;
    this->_valuestruct.Value.Float = f;
}

DataValue::DataValue(double d)
{
    this->_valuestruct.Endian = Endianness::platformEndian();
    this->_valuestruct.IsOverflowed = false;
    this->_valuestruct.IsSigned = true;
    this->_valuestruct.StringBuffer = nullptr;
    this->_valuestruct.Type = InternalType::Double;
    this->_valuestruct.Value.Double = d;
}

DataValue::DataValue(char ch)
{
    this->_valuestruct.Endian = Endianness::platformEndian();
    this->_valuestruct.IsOverflowed = false;
    this->_valuestruct.IsSigned = true;
    this->_valuestruct.StringBuffer = nullptr;
    this->_valuestruct.Type = InternalType::Character;
    this->_valuestruct.Value.Character = ch;
}

DataValue::DataValue(const char *s)
{
    this->_valuestruct.Endian = Endianness::platformEndian();
    this->_valuestruct.IsOverflowed = false;
    this->_valuestruct.IsSigned = false;
    this->_valuestruct.StringBuffer = nullptr;
    this->_valuestruct.Type = InternalType::String;
    this->_valuestruct.Value.AsciiString = s ? strdup(s) : nullptr;
}

DataValue::DataValue(const DataValue &dv)
{
    this->_valuestruct.Endian = Endianness::platformEndian();
    this->_valuestruct.Type = dv._valuestruct.Type;
    this->_valuestruct.IsOverflowed = dv._valuestruct.IsOverflowed;
    this->_valuestruct.IsSigned = dv._valuestruct.IsSigned;
    this->_valuestruct.StringBuffer = nullptr;

    if(this->_valuestruct.Type == InternalType::String)
        this->_valuestruct.Value.AsciiString = strdup(dv._valuestruct.Value.AsciiString);
    else
        this->_valuestruct.Value = dv._valuestruct.Value;
}

void DataValue::push(lua_State* l) const
{
    if(this->_valuestruct.Type == InternalType::String)
        lua_pushstring(l, this->_valuestruct.Value.AsciiString);
    else if(this->_valuestruct.Type == InternalType::Character)
        lua_pushlstring(l, &this->_valuestruct.Value.Character, 1);
    else if(this->_valuestruct.Type == InternalType::Float)
        lua_pushnumber(l, this->_valuestruct.Value.Float);
    else if(this->_valuestruct.Type == InternalType::Double)
        lua_pushnumber(l, this->_valuestruct.Value.Double);
    else if(this->_valuestruct.Type == InternalType::Integer)
    {
        if(this->_valuestruct.IsSigned)
            lua_pushinteger(l, this->_valuestruct.Value.Int64);
        else
            lua_pushinteger(l, this->_valuestruct.Value.UInt64);
    }
    else
        lua_pushnil(l);
}

void DataValue::castTo(DataType::Type type) // Let the compiler cast to the correct type
{
    if(type == DataType::Character)
    {
        this->_valuestruct.Type = DataValue::Character;
        return;
    }

    if(!DataType::isArithmetic(type))
        return;

    this->_valuestruct.IsSigned = DataType::isSigned(type);

    if(DataType::isFloatingPoint(type))
    {
        if(DataType::isFloat(type))
        {
            if(this->_valuestruct.Endian != DataType::endianness(type))
                Endianness::swap(&this->_valuestruct.Value.Float);

            this->_valuestruct.IsOverflowed = this->_valuestruct.Value.Float < std::numeric_limits<float>::min() ||
                                               this->_valuestruct.Value.Float > std::numeric_limits<float>::max();
        }
        else //if(DataType::isDouble(type))
        {
            if(this->_valuestruct.Endian != DataType::endianness(type))
                Endianness::swap(&this->_valuestruct.Value.Double);

            this->_valuestruct.IsOverflowed = this->_valuestruct.Value.Double < std::numeric_limits<double>::min() ||
                                               this->_valuestruct.Value.Double > std::numeric_limits<double>::max();
        }

        return;
    }

    size_t bits = DataType::bitWidth(type);

    if(this->_valuestruct.IsSigned)
    {
        if(bits == 8)
        {            
            this->_valuestruct.Value.Int64 = this->_valuestruct.Value.Int8;
            this->_valuestruct.IsOverflowed = this->_valuestruct.Value.Int64 < std::numeric_limits<int8_t>::min() ||
                                               this->_valuestruct.Value.Int64 > std::numeric_limits<int8_t>::max();
        }
        else if(bits == 16)
        {
            if(this->_valuestruct.Endian != DataType::endianness(type))
                Endianness::swap(&this->_valuestruct.Value.Int16);

            this->_valuestruct.Value.Int64 = this->_valuestruct.Value.Int16;
            this->_valuestruct.IsOverflowed = this->_valuestruct.Value.Int64 < std::numeric_limits<int16_t>::min() ||
                                               this->_valuestruct.Value.Int64 > std::numeric_limits<int16_t>::max();
        }
        else if(bits == 32)
        {
            if(this->_valuestruct.Endian != DataType::endianness(type))
                Endianness::swap(&this->_valuestruct.Value.Int32);

            this->_valuestruct.Value.Int64 = this->_valuestruct.Value.Int32;
            this->_valuestruct.IsOverflowed = this->_valuestruct.Value.Int64 < std::numeric_limits<int32_t>::min() ||
                                               this->_valuestruct.Value.Int64 > std::numeric_limits<int32_t>::max();
        }
        else
        {
            if(this->_valuestruct.Endian != DataType::endianness(type))
                Endianness::swap(&this->_valuestruct.Value.Int64);

            this->_valuestruct.IsOverflowed = false;
        }

        return;
    }

    if(bits == 8)
    {
        this->_valuestruct.Value.UInt64 = this->_valuestruct.Value.UInt8;
        this->_valuestruct.IsOverflowed = this->_valuestruct.Value.UInt64 < std::numeric_limits<uint8_t>::min() ||
                                           this->_valuestruct.Value.UInt64 > std::numeric_limits<uint8_t>::max();
    }
    else if(bits == 16)
    {
        if(this->_valuestruct.Endian != DataType::endianness(type))
            Endianness::swap(&this->_valuestruct.Value.UInt16);

        this->_valuestruct.Value.UInt64 = this->_valuestruct.Value.UInt16;
        this->_valuestruct.IsOverflowed = this->_valuestruct.Value.UInt64 < std::numeric_limits<uint16_t>::min() ||
                                           this->_valuestruct.Value.UInt64 > std::numeric_limits<uint16_t>::max();
    }
    else if(bits == 32)
    {
        if(this->_valuestruct.Endian != DataType::endianness(type))
            Endianness::swap(&this->_valuestruct.Value.UInt32);

        this->_valuestruct.Value.UInt64 = this->_valuestruct.Value.UInt32;
        this->_valuestruct.IsOverflowed = this->_valuestruct.Value.UInt64 < std::numeric_limits<uint32_t>::min() ||
                                           this->_valuestruct.Value.UInt64 > std::numeric_limits<uint32_t>::max();
    }
    else
    {
        if(this->_valuestruct.Endian != DataType::endianness(type))
            Endianness::swap(&this->_valuestruct.Value.UInt64);

        this->_valuestruct.IsOverflowed = false;
    }
}

bool DataValue::isNull() const
{
    return this->_valuestruct.Type == InternalType::Invalid;
}

bool DataValue::isZero() const
{
    return this->_valuestruct.Value.UInt64 == 0;
}

bool DataValue::isSigned() const
{
    return this->_valuestruct.IsSigned;
}

bool DataValue::isOverflowed() const
{
    return this->_valuestruct.IsOverflowed;
}

bool DataValue::isArithmetic() const
{
    return DataValue::isArithmetic(this->_valuestruct.Type);
}

bool DataValue::isIntegral() const
{
    return this->_valuestruct.Type == InternalType::Integer;
}

bool DataValue::isFloatingPoint() const
{
    return (this->_valuestruct.Type == InternalType::Float) || (this->_valuestruct.Type == InternalType::Double);
}

bool DataValue::isString() const
{
    return (this->_valuestruct.Type == InternalType::String) || (this->_valuestruct.Type == InternalType::Character);
}

bool DataValue::isCharacter() const
{
    return this->_valuestruct.Type == InternalType::Character;
}

DataValue::~DataValue()
{

}

const char *DataValue::toString(unsigned int base, unsigned int width)
{    
    if(this->_valuestruct.Type == InternalType::String)
        return this->_valuestruct.Value.AsciiString;

    if(this->_valuestruct.Type == InternalType::Character)
    {
        unsigned int len = sizeof(char);

        if(!this->_valuestruct.StringBuffer)
            this->_valuestruct.StringBuffer = new char[len + 1];

        this->_valuestruct.StringBuffer[len] = '\0';
        this->_valuestruct.StringBuffer[0] = this->_valuestruct.Value.Character;
        return this->_valuestruct.StringBuffer;
    }

    if(this->isArithmetic())
    {
        unsigned int len = sizeof(uintmax_t) * 8; // Use the biggest type's size (in bits)

        if(!this->_valuestruct.StringBuffer)
            this->_valuestruct.StringBuffer = new char[len + 1];

        this->_valuestruct.StringBuffer[len] = '\0';

        if(base == 2)
        {
            unsigned int len = 0;
            char* p = this->_valuestruct.StringBuffer + (len - 1);

            for(uintmax_t i = 0, b = this->_valuestruct.Value.UInt64; i < sizeof(uintmax_t); i++, b >>= 1)
            {
                if(b & 1)
                {
                    *p = '1';
                    len = p - this->_valuestruct.StringBuffer;
                }
                else
                    *p = '0';

                p--;
            }

            if(width)
                return (this->_valuestruct.StringBuffer + len) - width;

            return this->_valuestruct.StringBuffer + len;
        }
        else if(base == 8)
            snprintf(this->_valuestruct.StringBuffer, len, "%.*" PRIo64, width, (this->_valuestruct.IsSigned ? this->_valuestruct.Value.Int64 : this->_valuestruct.Value.UInt64));
        else if(base == 10)
            snprintf(this->_valuestruct.StringBuffer, len, (this->_valuestruct.IsSigned ? "%" PRId64 : "%" PRIu64), (this->_valuestruct.IsSigned ? this->_valuestruct.Value.Int64 : this->_valuestruct.Value.UInt64));
        else if(base == 16)
            snprintf(this->_valuestruct.StringBuffer, len, "%.*" PRIX64, width, this->_valuestruct.Value.UInt64);
        else
            throw std::runtime_error("Invalid Base");

        return this->_valuestruct.StringBuffer;
    }

    return nullptr;
}

Endianness::Type DataValue::endianness() const
{
    return this->_valuestruct.Endian;
}

DataValue DataValue::operator ~() const
{
    if(this->isArithmetic())
        throw std::runtime_error("Only arithmetic types can be negated");

    DataValue result = *this;
    result._valuestruct.Value.UInt64 = ~result._valuestruct.Value.UInt64;
    return result;
}

DataValue DataValue::operator &(const DataValue &rhs) const
{
    if(this->_valuestruct.Type != rhs._valuestruct.Type)
        throw std::runtime_error("Cannot do logical operation with different types");

    DataValue result = *this;

    if(result._valuestruct.IsSigned)
        result._valuestruct.Value.Int64 = this->_valuestruct.Value.Int64 & rhs._valuestruct.Value.Int64;
    else
        result._valuestruct.Value.UInt64 = this->_valuestruct.Value.UInt64 & rhs._valuestruct.Value.UInt64;

    return result;
}

DataValue DataValue::operator |(const DataValue &rhs) const
{
    if(this->_valuestruct.Type != rhs._valuestruct.Type)
        throw std::runtime_error("Cannot do logical operation with different types");

    DataValue result = *this;
    result._valuestruct.Value.UInt64 = this->_valuestruct.Value.UInt64 | rhs._valuestruct.Value.UInt64;
    return result;
}

DataValue DataValue::operator ^(const DataValue &rhs) const
{
    if(this->_valuestruct.Type != rhs._valuestruct.Type)
        throw std::runtime_error("Cannot do logical operation with different types");

    DataValue result = *this;
    result._valuestruct.Value.UInt64 = this->_valuestruct.Value.UInt64 ^ rhs._valuestruct.Value.UInt64;
    return result;
}

DataValue DataValue::operator <<(const DataValue &rhs) const
{
    if(this->_valuestruct.Type != rhs._valuestruct.Type)
        throw std::runtime_error("Cannot do logical operation with different types");

    DataValue result = *this;
    result._valuestruct.Value.UInt64 = this->_valuestruct.Value.UInt64 << rhs._valuestruct.Value.UInt64;
    return result;
}

DataValue DataValue::operator >>(const DataValue &rhs) const
{
    if(this->_valuestruct.Type != rhs._valuestruct.Type)
        throw std::runtime_error("Cannot do logical operation with different types");

    DataValue result = *this;
    result._valuestruct.Value.UInt64 = this->_valuestruct.Value.UInt64 >> rhs._valuestruct.Value.UInt64;
    return result;
}

bool DataValue::operator ==(const char *s) const
{
    return strcmp(this->_valuestruct.Value.AsciiString, s) == 0;
}

bool DataValue::operator !=(const char *s) const
{
    return strcmp(this->_valuestruct.Value.AsciiString, s) != 0;
}

unsigned char *DataValue::operator &()
{
    return reinterpret_cast<unsigned char*>(&this->_valuestruct.Value);
}

PrefLib::DataValue::operator const char *() const
{
    return this->_valuestruct.Value.AsciiString;
}

PrefLib::DataValue::operator float() const
{
    return this->_valuestruct.Value.Float;
}

PrefLib::DataValue::operator double() const
{
    return this->_valuestruct.Value.Double;
}

PrefLib::DataValue::operator int8_t() const
{
    return this->_valuestruct.Value.Int8;
}

PrefLib::DataValue::operator int16_t() const
{
    return this->_valuestruct.Value.Int16;
}

PrefLib::DataValue::operator int32_t() const
{
    return this->_valuestruct.Value.Int32;
}

PrefLib::DataValue::operator int64_t() const
{
    return this->_valuestruct.Value.Int64;
}

PrefLib::DataValue::operator uint8_t() const
{
    return this->_valuestruct.Value.UInt8;
}

PrefLib::DataValue::operator uint16_t() const
{
    return this->_valuestruct.Value.UInt16;
}

PrefLib::DataValue::operator uint32_t() const
{
    return this->_valuestruct.Value.UInt32;
}

PrefLib::DataValue::operator uint64_t() const
{
    return this->_valuestruct.Value.UInt64;
}

bool DataValue::operator ==(const DataValue &rhs) const
{
    return this->_valuestruct.Value.Int64 == rhs._valuestruct.Value.Int64;
}

bool DataValue::operator !=(const DataValue &rhs) const
{
    return this->_valuestruct.Value.Int64 != rhs._valuestruct.Value.Int64;
}

bool DataValue::operator >(const DataValue &rhs) const
{
    return this->_valuestruct.Value.Int64 > rhs._valuestruct.Value.Int64;
}

bool DataValue::operator <(const DataValue &rhs) const
{
    return this->_valuestruct.Value.Int64 < rhs._valuestruct.Value.Int64;
}

bool DataValue::operator >=(const DataValue &rhs) const
{
    return this->_valuestruct.Value.Int64 >= rhs._valuestruct.Value.Int64;
}

bool DataValue::operator <=(const DataValue &rhs) const
{
    return this->_valuestruct.Value.Int64 <= rhs._valuestruct.Value.Int64;
}

DataValue& DataValue::operator ++()
{
    ++this->_valuestruct.Value.Int64;
    return *this;
}

DataValue& DataValue::operator --()
{
    --this->_valuestruct.Value.Int64;
    return *this;
}

DataValue DataValue::operator ++(int) const
{
    DataValue result = *this;
    ++result._valuestruct.Value.Int64;
    return result;
}

DataValue DataValue::operator --(int) const
{
    DataValue result = *this;
    --result._valuestruct.Value.Int64;
    return result;
}

DataValue DataValue::operator +(const DataValue &rhs) const
{
    if(this->_valuestruct.Type != rhs._valuestruct.Type)
        throw std::runtime_error("Cannot add DataValues with different types");

    if(this->_valuestruct.Type == InternalType::Invalid)
        return DataValue();

    DataValue dv;
    dv._valuestruct.Type = this->_valuestruct.Type;

    if(this->_valuestruct.Type == InternalType::String)
    {
        int len1 = strlen(this->_valuestruct.Value.AsciiString), len2 = strlen(rhs._valuestruct.Value.AsciiString);
        dv._valuestruct.Value.AsciiString = new char[len1 + len2 + 1];
        strcpy(dv._valuestruct.Value.AsciiString, this->_valuestruct.Value.AsciiString);
        strcpy(dv._valuestruct.Value.AsciiString + len1, rhs._valuestruct.Value.AsciiString);
        dv._valuestruct.Value.AsciiString[len1 + len2] = '\0';
    }
    else if(this->_valuestruct.Type == InternalType::Float)
        dv._valuestruct.Value.Float = this->_valuestruct.Value.Float + rhs._valuestruct.Value.Float;
    else if(this->_valuestruct.Type == InternalType::Double)
        dv._valuestruct.Value.Double = this->_valuestruct.Value.Double + rhs._valuestruct.Value.Double;
    else
        dv._valuestruct.Value.UInt64 = this->_valuestruct.Value.UInt64 + rhs._valuestruct.Value.UInt64;

    return dv;
}

DataValue DataValue::operator -(const DataValue &rhs) const
{
    if(this->_valuestruct.Type != rhs._valuestruct.Type)
        throw std::runtime_error("Cannot add DataValues with different types");

    if(this->_valuestruct.Type == InternalType::String)
        throw std::runtime_error("Cannot use '-' operator with strings");

    if(this->_valuestruct.Type == InternalType::Invalid)
        return DataValue();

    DataValue dv;
    dv._valuestruct.Type = this->_valuestruct.Type;

    if(this->_valuestruct.Type == InternalType::Float)
        dv._valuestruct.Value.Float = this->_valuestruct.Value.Float - rhs._valuestruct.Value.Float;
    else if(this->_valuestruct.Type == InternalType::Double)
        dv._valuestruct.Value.Double = this->_valuestruct.Value.Double - rhs._valuestruct.Value.Double;
    else
        dv._valuestruct.Value.UInt64 = this->_valuestruct.Value.UInt64 - rhs._valuestruct.Value.UInt64;

    return dv;
}

DataValue& DataValue::operator +=(const DataValue &rhs)
{
    if(this->_valuestruct.Type != rhs._valuestruct.Type)
        throw std::runtime_error("Cannot add DataValues with different types");

    if(this->_valuestruct.Type == InternalType::Invalid)
        throw std::runtime_error("DataValue is null");

    if(this->_valuestruct.Type == InternalType::String)
    {
        int len1 = strlen(this->_valuestruct.Value.AsciiString), len2 = strlen(rhs._valuestruct.Value.AsciiString);
        const char* oldstring = this->_valuestruct.Value.AsciiString;

        this->_valuestruct.Value.AsciiString = new char[len1 + len2 + 1];
        strcpy(this->_valuestruct.Value.AsciiString, oldstring);
        strcpy(this->_valuestruct.Value.AsciiString + len1, rhs._valuestruct.Value.AsciiString);

        this->_valuestruct.Value.AsciiString[len1 + len2] = '\0';
        delete[] oldstring;
    }
    else if(this->_valuestruct.Type == InternalType::Float)
        this->_valuestruct.Value.Float += rhs._valuestruct.Value.Float;
    else if(this->_valuestruct.Type == InternalType::Double)
        this->_valuestruct.Value.Double += rhs._valuestruct.Value.Double;
    else
        this->_valuestruct.Value.UInt64 += rhs._valuestruct.Value.UInt64;

    return *this;
}

DataValue& DataValue::operator -=(const DataValue &rhs)
{
    if(this->_valuestruct.Type != rhs._valuestruct.Type)
        throw std::runtime_error("Cannot add DataValues with different types");

    if(this->_valuestruct.Type == InternalType::String)
        throw std::runtime_error("Cannot use '-=' operator with strings");

    if(this->_valuestruct.Type == InternalType::Invalid)
        throw std::runtime_error("DataValue is null");

    if(this->_valuestruct.Type == InternalType::Float)
        this->_valuestruct.Value.Float -= rhs._valuestruct.Value.Float;
    else if(this->_valuestruct.Type == InternalType::Double)
        this->_valuestruct.Value.Double -= rhs._valuestruct.Value.Double;
    else
        this->_valuestruct.Value.UInt64 -= rhs._valuestruct.Value.UInt64;

    return *this;
}

DataValue& DataValue::operator =(const DataValue &rhs)
{
    this->_valuestruct = rhs._valuestruct;
    return *this;
}

} // namespace PrefLib
