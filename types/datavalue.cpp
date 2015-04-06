#include "datavalue.h"

namespace PrefLib {

int DataValue::luaMetaGc(lua_State *l)
{
    UserData* userdata = reinterpret_cast<UserData*>(luaL_checkudata(l, 1, "datavalue"));

    if(userdata->StringBuffer)
    {
        delete[] userdata->StringBuffer;
        userdata->StringBuffer = nullptr;
    }

    return 0;
}

int DataValue::luaMetaIndex(lua_State *l)
{
    UserData* userdata = reinterpret_cast<UserData*>(luaL_checkudata(l, 1, "datavalue"));
    const char* arg = lua_tostring(l, 2);

    if(((userdata->Type == InternalType::Real) || (userdata->Type == InternalType::Integer)) && !strcmp(arg, "number"))
    {
        if(userdata->Type == InternalType::Real)
            lua_pushnumber(l, userdata->Value.Real);
        if(userdata->IsSigned)
            lua_pushinteger(l, userdata->Value.Int64);
        else
            lua_pushinteger(l, userdata->Value.UInt64);
    }
    else if((userdata->Type == InternalType::String) && !strcmp(arg, "string"))
        lua_pushstring(l, userdata->Value.AsciiString);
    else
        lua_pushnil(l);

    return 1;
}

int DataValue::luaMetaNewIndex(lua_State *l)
{
    UserData* userdata = reinterpret_cast<UserData*>(luaL_checkudata(l, 1, "datavalue"));
    const char* arg = lua_tostring(l, 2);

    if(((userdata->Type == InternalType::Real) || (userdata->Type == InternalType::Integer)) && !strcmp(arg, "number"))
    {
        if(userdata->Type == InternalType::Real)
            userdata->Value.Real = luaL_checknumber(l, 3);
        if(userdata->IsSigned)
            userdata->Value.Int64 = luaL_checkinteger(l, 3);
        else
            userdata->Value.UInt64 = luaL_checkinteger(l, 3);
    }
    else if((userdata->Type == InternalType::String) && !strcmp(arg, "string"))
    {
        if(userdata->Value.AsciiString)
            delete[] userdata->Value.AsciiString;

        const char* s = luaL_checkstring(l, 3);
        int len = strlen(s);
        userdata->Value.AsciiString = new char[len + 1];
        userdata->Value.AsciiString[len] = '\0';
        strcpy(userdata->Value.AsciiString, s);
    }

    luaL_error(l, "Field '%s' not found", arg);
    return 0;
}

int DataValue::luaMetaUnm(lua_State *l)
{
    UserData* userdata = reinterpret_cast<UserData*>(luaL_checkudata(l, 1, "datavalue"));

    if(userdata->Type == InternalType::String)
        lua_pushnil(l);
    else
    {
        DataValue dv = -userdata->Value.Int32;
        dv.push();
    }

    return 1;
}

int DataValue::luaMetaAdd(lua_State *l)
{
    UserData* userdata = reinterpret_cast<UserData*>(luaL_checkudata(l, 1, "datavalue"));

    if(userdata->Type == InternalType::String)
        lua_pushnil(l);
    else if((userdata->Type == InternalType::Real) || (userdata->Type == InternalType::Integer))
    {
        int t = lua_type(l, 2);

        if(userdata->Type == InternalType::Real)
        {
            DataValue dv = userdata->Value.Real + ((t == LUA_TNUMBER) ? lua_tonumber(l, 2) :
                                                                        reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Real);
            dv.push();
        }
        else if(userdata->IsSigned)
        {
            DataValue dv = userdata->Value.Int64 + ((t == LUA_TNUMBER) ? lua_tointeger(l, 2) :
                                                                         reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Int64);
            dv.push();
        }
        else
        {
            DataValue dv = userdata->Value.UInt64 + ((t == LUA_TNUMBER) ? lua_tointeger(l, 2) :
                                                                          reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Int64);
            dv.push();
        }
    }

    return 1;
}

int DataValue::luaMetaSub(lua_State *l)
{
    UserData* userdata = reinterpret_cast<UserData*>(luaL_checkudata(l, 1, "datavalue"));

    if(userdata->Type == InternalType::String)
        lua_pushnil(l);
    else if((userdata->Type == InternalType::Real) || (userdata->Type == InternalType::Integer))
    {
        int t = lua_type(l, 2);

        if(userdata->Type == InternalType::Real)
        {
            DataValue dv = userdata->Value.Real - ((t == LUA_TNUMBER) ? lua_tonumber(l, 2) :
                                                                        reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Real);
            dv.push();
        }
        else if(userdata->IsSigned)
        {
            DataValue dv = userdata->Value.Int64 - ((t == LUA_TNUMBER) ? lua_tointeger(l, 2) :
                                                                         reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Int64);
            dv.push();
        }
        else
        {
            DataValue dv = userdata->Value.UInt64 - ((t == LUA_TNUMBER) ? lua_tointeger(l, 2) :
                                                                          reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Int64);
            dv.push();
        }
    }

    return 1;
}

int DataValue::luaMetaMul(lua_State *l)
{
    UserData* userdata = reinterpret_cast<UserData*>(luaL_checkudata(l, 1, "datavalue"));

    if(userdata->Type == InternalType::String)
        lua_pushnil(l);
    else if((userdata->Type == InternalType::Real) || (userdata->Type == InternalType::Integer))
    {
        int t = lua_type(l, 2);

        if(userdata->Type == InternalType::Real)
        {
            DataValue dv = userdata->Value.Real * ((t == LUA_TNUMBER) ? lua_tonumber(l, 2) :
                                                                        reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Real);
            dv.push();
        }
        else if(userdata->IsSigned)
        {
            DataValue dv = userdata->Value.Int64 * ((t == LUA_TNUMBER) ? lua_tointeger(l, 2) :
                                                                         reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Int64);
            dv.push();
        }
        else
        {
            DataValue dv = userdata->Value.UInt64 * ((t == LUA_TNUMBER) ? lua_tointeger(l, 2) :
                                                                          reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Int64);
            dv.push();
        }
    }

    return 1;
}

int DataValue::luaMetaDiv(lua_State *l)
{
    UserData* userdata = reinterpret_cast<UserData*>(luaL_checkudata(l, 1, "datavalue"));

    if(userdata->Type == InternalType::String)
        lua_pushnil(l);
    else if((userdata->Type == InternalType::Real) || (userdata->Type == InternalType::Integer))
    {
        int t = lua_type(l, 2);

        if(userdata->Type == InternalType::Real)
        {
            DataValue dv = userdata->Value.Real / ((t == LUA_TNUMBER) ? lua_tonumber(l, 2) :
                                                                        reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Real);
            dv.push();
        }
        else if(userdata->IsSigned)
        {
            DataValue dv = userdata->Value.Int64 / ((t == LUA_TNUMBER) ? lua_tointeger(l, 2) :
                                                                         reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Int64);
            dv.push();
        }
        else
        {
            DataValue dv = userdata->Value.UInt64 / ((t == LUA_TNUMBER) ? lua_tointeger(l, 2) :
                                                                          reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Int64);
            dv.push();
        }
    }

    return 1;
}

int DataValue::luaMetaMod(lua_State *l)
{
    UserData* userdata = reinterpret_cast<UserData*>(luaL_checkudata(l, 1, "datavalue"));

    if(userdata->Type == InternalType::String)
        lua_pushnil(l);
    else if((userdata->Type == InternalType::Real) || (userdata->Type == InternalType::Integer))
    {
        int t = lua_type(l, 2);

        if(userdata->Type == InternalType::Real)
        {
            DataValue dv = fmod(userdata->Value.Real, ((t == LUA_TNUMBER) ? lua_tonumber(l, 2) :
                                                                            reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Real));
            dv.push();
        }
        else if(userdata->IsSigned)
        {
            DataValue dv = userdata->Value.Int64 % ((t == LUA_TNUMBER) ? lua_tointeger(l, 2) :
                                                                         reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Int64);
            dv.push();
        }
        else
        {
            DataValue dv = userdata->Value.UInt64 % ((t == LUA_TNUMBER) ? lua_tointeger(l, 2) :
                                                                          reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Int64);
            dv.push();
        }
    }

    return 1;
}

int DataValue::luaMetaPow(lua_State *l)
{
    UserData* userdata = reinterpret_cast<UserData*>(luaL_checkudata(l, 1, "datavalue"));

    if(userdata->Type == InternalType::String)
        lua_pushnil(l);
    else if((userdata->Type == InternalType::Real) || (userdata->Type == InternalType::Integer))
    {
        int t = lua_type(l, 2);

        if(userdata->Type == InternalType::Real)
        {
            DataValue dv = pow(userdata->Value.Real, ((t == LUA_TNUMBER) ? lua_tonumber(l, 2) :
                                                                           reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Real));
            dv.push();
        }
        else if(userdata->IsSigned)
        {
            DataValue dv = pow(userdata->Value.Int64, ((t == LUA_TNUMBER) ? lua_tointeger(l, 2) :
                                                                            reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Int64));
            dv.push();
        }
        else
        {
            DataValue dv = pow(userdata->Value.UInt64, ((t == LUA_TNUMBER) ? lua_tointeger(l, 2) :
                                                                             reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"))->Value.Int64));
            dv.push();
        }
    }

    return 1;
}

int DataValue::luaMetaLen(lua_State *l)
{
    UserData* userdata = reinterpret_cast<UserData*>(luaL_checkudata(l, 1, "datavalue"));

    if(userdata->Type == InternalType::String)
        lua_pushinteger(l, strlen(userdata->Value.AsciiString));
    else if(userdata->Type == InternalType::Real)
        lua_pushinteger(l, 8);
    else if(userdata->Type == InternalType::Integer)
    {
        if(userdata->Value.UInt64 <= 0xFF)
            lua_pushinteger(l, 1);
        else if(userdata->Value.UInt64 <= 0xFFFF)
            lua_pushinteger(l, 2);
        else if(userdata->Value.UInt64 <= 0xFFFFFFFF)
            lua_pushinteger(l, 4);
        else if(userdata->Value.UInt64 <= 0xFFFFFFFFFFFFFFFF)
            lua_pushinteger(l, 8);
        else
            lua_pushinteger(l, 0);
    }
    else
        lua_pushinteger(l, 0);

    return 1;
}

int DataValue::luaMetaEq(lua_State *l)
{
    UserData* userdata1 = reinterpret_cast<UserData*>(luaL_checkudata(l, 1, "datavalue"));
    UserData* userdata2 = reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"));

    if(userdata1->Type != userdata2->Type)
    {
        lua_pushboolean(l, false);
        return 1;
    }

    if(userdata1->Type == InternalType::Integer)
    {
        if(userdata1->IsSigned)
            lua_pushboolean(l, (userdata1->Value.Int64 == userdata2->Value.Int64));
        else
            lua_pushboolean(l, (userdata1->Value.UInt64 == userdata2->Value.UInt64));
    }
    else if(userdata1->Type == InternalType::Real)
        lua_pushboolean(l, (userdata1->Value.Real == userdata2->Value.Real));
    else if(userdata1->Type == InternalType::String)
        lua_pushboolean(l, !strcmp(userdata1->Value.AsciiString, userdata2->Value.AsciiString));
    else
        lua_pushboolean(l, false);

    return 1;
}

int DataValue::luaMetaLt(lua_State *l)
{
    UserData* userdata1 = reinterpret_cast<UserData*>(luaL_checkudata(l, 1, "datavalue"));
    UserData* userdata2 = reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"));

    if(userdata1->Type != userdata2->Type)
    {
        lua_pushboolean(l, false);
        return 1;
    }

    if(userdata1->Type == InternalType::Integer)
    {
        if(userdata1->IsSigned)
            lua_pushboolean(l, (userdata1->Value.Int64 < userdata2->Value.Int64));
        else
            lua_pushboolean(l, (userdata1->Value.UInt64 < userdata2->Value.UInt64));
    }
    else if(userdata1->Type == InternalType::Real)
        lua_pushboolean(l, (userdata1->Value.Real == userdata2->Value.Real));
    else
        lua_pushboolean(l, false);

    return 1;
}

int DataValue::luaMetaLe(lua_State *l)
{
    UserData* userdata1 = reinterpret_cast<UserData*>(luaL_checkudata(l, 1, "datavalue"));
    UserData* userdata2 = reinterpret_cast<UserData*>(luaL_checkudata(l, 2, "datavalue"));

    if(userdata1->Type != userdata2->Type)
    {
        lua_pushboolean(l, false);
        return 1;
    }

    if(userdata1->Type == InternalType::Integer)
    {
        if(userdata1->IsSigned)
            lua_pushboolean(l, (userdata1->Value.Int64 <= userdata2->Value.Int64));
        else
            lua_pushboolean(l, (userdata1->Value.UInt64 <= userdata2->Value.UInt64));
    }
    else if(userdata1->Type == InternalType::Real)
        lua_pushboolean(l, (userdata1->Value.Real == userdata2->Value.Real));
    else
        lua_pushboolean(l, false);

    return 1;
}

void DataValue::allocateUserData()
{
    lua_State* l = Core::LuaState::instance();
    this->_valuestruct = reinterpret_cast<UserData*>(lua_newuserdata(l, sizeof(UserData)));

    if(luaL_newmetatable(l, "datavalue"))
    {
        lua_pushcfunction(l, &DataValue::luaMetaGc);
        lua_setfield(l, -2, "__gc");

        lua_pushcfunction(l, &DataValue::luaMetaIndex);
        lua_setfield(l, -2, "__index");

        lua_pushcfunction(l, &DataValue::luaMetaNewIndex);
        lua_setfield(l, -2, "__newindex");

        lua_pushcfunction(l, &DataValue::luaMetaUnm);
        lua_setfield(l, -2, "__unm");

        lua_pushcfunction(l, &DataValue::luaMetaAdd);
        lua_setfield(l, -2, "__add");

        lua_pushcfunction(l, &DataValue::luaMetaSub);
        lua_setfield(l, -2, "__sub");

        lua_pushcfunction(l, &DataValue::luaMetaMul);
        lua_setfield(l, -2, "__mul");

        lua_pushcfunction(l, &DataValue::luaMetaDiv);
        lua_setfield(l, -2, "__div");

        lua_pushcfunction(l, &DataValue::luaMetaMod);
        lua_setfield(l, -2, "__mod");

        lua_pushcfunction(l, &DataValue::luaMetaPow);
        lua_setfield(l, -2, "__pow");

        lua_pushcfunction(l, &DataValue::luaMetaLen);
        lua_setfield(l, -2, "__len");

        lua_pushcfunction(l, &DataValue::luaMetaEq);
        lua_setfield(l, -2, "__eq");

        lua_pushcfunction(l, &DataValue::luaMetaLt);
        lua_setfield(l, -2, "__lt");

        lua_pushcfunction(l, &DataValue::luaMetaLe);
        lua_setfield(l, -2, "__le");
    }

    lua_setmetatable(l, -2);
    this->_reference = luaL_ref(l, LUA_REGISTRYINDEX);
}

DataValue::DataValue(): Core::LuaReference()
{
    this->allocateUserData();

    this->_valuestruct->Endian = Endianness::platformEndian();
    this->_valuestruct->IsOverflowed = false;
    this->_valuestruct->IsSigned = false;
    this->_valuestruct->StringBuffer = nullptr;
    this->_valuestruct->Type = InternalType::Invalid;
    this->_valuestruct->Value.UInt64 = 0u;
}

DataValue::DataValue(double d): Core::LuaReference()
{
    this->allocateUserData();

    this->_valuestruct->Endian = Endianness::platformEndian();
    this->_valuestruct->IsOverflowed = false;
    this->_valuestruct->IsSigned = true;
    this->_valuestruct->StringBuffer = nullptr;
    this->_valuestruct->Type = InternalType::Real;
    this->_valuestruct->Value.Real = d;
}

DataValue::DataValue(const char *ch): Core::LuaReference()
{
    this->allocateUserData();

    this->_valuestruct->Endian = Endianness::platformEndian();
    this->_valuestruct->IsOverflowed = false;
    this->_valuestruct->IsSigned = false;
    this->_valuestruct->StringBuffer = nullptr;
    this->_valuestruct->Type = InternalType::String;
    this->_valuestruct->Value.AsciiString = ch ? strdup(ch) : nullptr;
}

DataValue::DataValue(const DataValue &dv): Core::LuaReference(dv)
{
    this->allocateUserData();

    this->_valuestruct->Endian = Endianness::platformEndian();
    this->_valuestruct->IsOverflowed = false;
    this->_valuestruct->IsSigned = false;
    this->_valuestruct->StringBuffer = nullptr;
    this->_valuestruct->Type = dv._valuestruct->Type;

    if(this->_valuestruct->Type == InternalType::String)
        this->_valuestruct->Value.AsciiString = strdup(dv._valuestruct->Value.AsciiString);
    else
        this->_valuestruct->Value = dv._valuestruct->Value;
}

void DataValue::push() const
{
    lua_State* l = Core::LuaState::instance();
    LuaReference::push();

    if(this->_valuestruct->Type == InternalType::String)
        lua_pushstring(l, this->_valuestruct->Value.AsciiString);
    else if(this->_valuestruct->Type == InternalType::Real)
        lua_pushnumber(l, this->_valuestruct->Value.Real);
    else if(this->_valuestruct->Type == InternalType::Integer)
    {
        if(this->_valuestruct->IsSigned)
            lua_pushinteger(l, this->_valuestruct->Value.Int64);
        else
            lua_pushinteger(l, this->_valuestruct->Value.UInt64);
    }
    else
        lua_pushnil(l);

    lua_remove(l, -2);
}

void DataValue::castTo(DataType::Type type)
{
    if(!DataType::isInteger(type)) //TODO: Floating Point + Endianness?
        return;

    this->_valuestruct->IsSigned = DataType::isSigned(type);

    /* Let the compiler cast to the correct type */
    size_t bits = DataType::bitWidth(type);

    if(this->_valuestruct->IsSigned)
    {
        if(bits == 8)
        {            
            this->_valuestruct->Value.Int64 = this->_valuestruct->Value.Int8;
            this->_valuestruct->IsOverflowed = this->_valuestruct->Value.Int64 < std::numeric_limits<int8_t>::min() ||
                                               this->_valuestruct->Value.Int64 > std::numeric_limits<int8_t>::max();
        }
        else if(bits == 16)
        {
            if(this->_valuestruct->Endian != DataType::endianness(type))
                Endianness::swapEndianness(&this->_valuestruct->Value.Int16);

            this->_valuestruct->Value.Int64 = this->_valuestruct->Value.Int16;
            this->_valuestruct->IsOverflowed = this->_valuestruct->Value.Int64 < std::numeric_limits<int16_t>::min() ||
                                               this->_valuestruct->Value.Int64 > std::numeric_limits<int16_t>::max();
        }
        else if(bits == 32)
        {
            if(this->_valuestruct->Endian != DataType::endianness(type))
                Endianness::swapEndianness(&this->_valuestruct->Value.Int32);

            this->_valuestruct->Value.Int64 = this->_valuestruct->Value.Int32;
            this->_valuestruct->IsOverflowed = this->_valuestruct->Value.Int64 < std::numeric_limits<int32_t>::min() ||
                                               this->_valuestruct->Value.Int64 > std::numeric_limits<int32_t>::max();
        }
        else
        {
            if(this->_valuestruct->Endian != DataType::endianness(type))
                Endianness::swapEndianness(&this->_valuestruct->Value.Int64);

            this->_valuestruct->IsOverflowed = false;
        }

        return;
    }

    if(bits == 8)
    {
        this->_valuestruct->Value.UInt64 = this->_valuestruct->Value.UInt8;
        this->_valuestruct->IsOverflowed = this->_valuestruct->Value.UInt64 > std::numeric_limits<uint8_t>::min() ||
                                           this->_valuestruct->Value.UInt64 > std::numeric_limits<uint8_t>::max();
    }
    else if(bits == 16)
    {
        if(this->_valuestruct->Endian != DataType::endianness(type))
            Endianness::swapEndianness(&this->_valuestruct->Value.UInt16);

        this->_valuestruct->Value.UInt64 = this->_valuestruct->Value.UInt16;
        this->_valuestruct->IsOverflowed = this->_valuestruct->Value.UInt64 > std::numeric_limits<uint16_t>::min() ||
                                           this->_valuestruct->Value.UInt64 > std::numeric_limits<uint16_t>::max();
    }
    else if(bits == 32)
    {
        if(this->_valuestruct->Endian != DataType::endianness(type))
            Endianness::swapEndianness(&this->_valuestruct->Value.UInt32);

        this->_valuestruct->Value.UInt64 = this->_valuestruct->Value.UInt32;
        this->_valuestruct->IsOverflowed = this->_valuestruct->Value.UInt64 > std::numeric_limits<uint32_t>::min() ||
                                           this->_valuestruct->Value.UInt64 > std::numeric_limits<uint32_t>::max();
    }
    else
    {
        if(this->_valuestruct->Endian != DataType::endianness(type))
            Endianness::swapEndianness(&this->_valuestruct->Value.UInt64);

        this->_valuestruct->IsOverflowed = false;
    }
}

bool DataValue::isNull() const
{
    return this->_valuestruct->Type == InternalType::Invalid;
}

bool DataValue::isZero() const
{
    return this->_valuestruct->Value.UInt64 == 0;
}

bool DataValue::isOverflowed() const
{
    return this->_valuestruct->IsOverflowed;
}

DataValue::~DataValue()
{

}

const char *DataValue::toString(unsigned int base, unsigned int width)
{
    if(this->_valuestruct->Type == InternalType::String)
        return this->_valuestruct->Value.AsciiString;

    if((this->_valuestruct->Type == InternalType::Integer) || (this->_valuestruct->Type == InternalType::Real))
    {
        unsigned int sz = sizeof(uintmax_t) * 8; // Use the biggest type's size (in bits)

        if(!this->_valuestruct->StringBuffer)
            this->_valuestruct->StringBuffer = new char[sz + 1];

        this->_valuestruct->StringBuffer[sz] = '\0';

        if(base == 2)
        {
            unsigned int len = 0;
            char* p = this->_valuestruct->StringBuffer + (sz - 1);

            for(uintmax_t i = 0, b = this->_valuestruct->Value.UInt64; i < sizeof(uintmax_t); i++, b >>= 1)
            {
                if(b & 1)
                {
                    *p = '1';
                    len = p - this->_valuestruct->StringBuffer;
                }
                else
                    *p = '0';

                p--;
            }

            if(width)
                return (this->_valuestruct->StringBuffer + sz) - width;

            return this->_valuestruct->StringBuffer + len;
        }
        else if(base == 8)
            snprintf(this->_valuestruct->StringBuffer, sz, "%.*" PRIo64, width, (this->_valuestruct->IsSigned ? this->_valuestruct->Value.Int64 : this->_valuestruct->Value.UInt64));
        else if(base == 10)
            snprintf(this->_valuestruct->StringBuffer, sz, (this->_valuestruct->IsSigned ? "%" PRId64 : "%" PRIu64), (this->_valuestruct->IsSigned ? this->_valuestruct->Value.Int64 : this->_valuestruct->Value.UInt64));
        else if(base == 16)
            snprintf(this->_valuestruct->StringBuffer, sz, "%.*" PRIX64, width, this->_valuestruct->Value.UInt64);
        else
            throw std::runtime_error("Invalid Base");

        return this->_valuestruct->StringBuffer;
    }

    return nullptr;
}

unsigned char *DataValue::operator &()
{
    return reinterpret_cast<unsigned char*>(&this->_valuestruct->Value);
}

DataValue DataValue::operator ~() const
{
    if((this->_valuestruct->Type != InternalType::Integer) && (this->_valuestruct->Type != InternalType::Real))
        throw std::runtime_error("Only numeric types can be negated");

    DataValue result = *this;
    result._valuestruct->Value.UInt64 = ~result._valuestruct->Value.UInt64;
    return result;
}

DataValue DataValue::operator &(const DataValue &rhs) const
{
    if(this->_valuestruct->Type != rhs._valuestruct->Type)
        throw std::runtime_error("Cannot do logical operation with different types");

    DataValue result = *this;

    if(result._valuestruct->IsSigned)
        result._valuestruct->Value.Int64 = this->_valuestruct->Value.Int64 & rhs._valuestruct->Value.Int64;
    else
        result._valuestruct->Value.UInt64 = this->_valuestruct->Value.UInt64 & rhs._valuestruct->Value.UInt64;

    return result;
}

DataValue DataValue::operator |(const DataValue &rhs) const
{
    if(this->_valuestruct->Type != rhs._valuestruct->Type)
        throw std::runtime_error("Cannot do logical operation with different types");

    DataValue result = *this;
    result._valuestruct->Value.UInt64 = this->_valuestruct->Value.UInt64 | rhs._valuestruct->Value.UInt64;
    return result;
}

DataValue DataValue::operator ^(const DataValue &rhs) const
{
    if(this->_valuestruct->Type != rhs._valuestruct->Type)
        throw std::runtime_error("Cannot do logical operation with different types");

    DataValue result = *this;
    result._valuestruct->Value.UInt64 = this->_valuestruct->Value.UInt64 ^ rhs._valuestruct->Value.UInt64;
    return result;
}

DataValue DataValue::operator <<(const DataValue &rhs) const
{
    if(this->_valuestruct->Type != rhs._valuestruct->Type)
        throw std::runtime_error("Cannot do logical operation with different types");

    DataValue result = *this;
    result._valuestruct->Value.UInt64 = this->_valuestruct->Value.UInt64 << rhs._valuestruct->Value.UInt64;
    return result;
}

DataValue DataValue::operator >>(const DataValue &rhs) const
{
    if(this->_valuestruct->Type != rhs._valuestruct->Type)
        throw std::runtime_error("Cannot do logical operation with different types");

    DataValue result = *this;
    result._valuestruct->Value.UInt64 = this->_valuestruct->Value.UInt64 >> rhs._valuestruct->Value.UInt64;
    return result;
}

PrefLib::DataValue::operator double()
{
    return this->_valuestruct->Value.Real;
}

bool DataValue::operator ==(const char *s) const
{
    return strcmp(this->_valuestruct->Value.AsciiString, s) == 0;
}

bool DataValue::operator !=(const char *s) const
{
    return strcmp(this->_valuestruct->Value.AsciiString, s) != 0;
}

PrefLib::DataValue::operator const char *()
{
    return this->_valuestruct->Value.AsciiString;
}

PrefLib::DataValue::operator int8_t()
{
    return this->_valuestruct->Value.Int8;
}

PrefLib::DataValue::operator int16_t()
{
    return this->_valuestruct->Value.Int16;
}

PrefLib::DataValue::operator int32_t()
{
    return this->_valuestruct->Value.Int32;
}

PrefLib::DataValue::operator int64_t()
{
    return this->_valuestruct->Value.Int64;
}

PrefLib::DataValue::operator uint8_t()
{
    return this->_valuestruct->Value.UInt8;
}

PrefLib::DataValue::operator uint16_t()
{
    return this->_valuestruct->Value.UInt16;
}

PrefLib::DataValue::operator uint32_t()
{
    return this->_valuestruct->Value.UInt32;
}

PrefLib::DataValue::operator uint64_t()
{
    return this->_valuestruct->Value.UInt64;
}

bool DataValue::operator ==(const DataValue &rhs) const
{
    return this->_valuestruct->Value.Int64 == rhs._valuestruct->Value.Int64;
}

bool DataValue::operator !=(const DataValue &rhs) const
{
    return this->_valuestruct->Value.Int64 != rhs._valuestruct->Value.Int64;
}

bool DataValue::operator >(const DataValue &rhs) const
{
    return this->_valuestruct->Value.Int64 > rhs._valuestruct->Value.Int64;
}

bool DataValue::operator <(const DataValue &rhs) const
{
    return this->_valuestruct->Value.Int64 < rhs._valuestruct->Value.Int64;
}

bool DataValue::operator >=(const DataValue &rhs) const
{
    return this->_valuestruct->Value.Int64 >= rhs._valuestruct->Value.Int64;
}

bool DataValue::operator <=(const DataValue &rhs) const
{
    return this->_valuestruct->Value.Int64 <= rhs._valuestruct->Value.Int64;
}

DataValue& DataValue::operator ++()
{
    ++this->_valuestruct->Value.Int64;
    return *this;
}

DataValue& DataValue::operator --()
{
    --this->_valuestruct->Value.Int64;
    return *this;
}

DataValue DataValue::operator ++(int) const
{
    DataValue result = *this;
    ++this->_valuestruct->Value.Int64;
    return result;
}

DataValue DataValue::operator --(int) const
{
    DataValue result = *this;
    --this->_valuestruct->Value.Int64;
    return result;
}

DataValue DataValue::operator +(const DataValue &rhs) const
{
    if(this->_valuestruct->Type != rhs._valuestruct->Type)
        throw std::runtime_error("Cannot add DataValues with different types");

    if(this->_valuestruct->Type == InternalType::Invalid)
        return DataValue();

    DataValue dv;
    dv._valuestruct->Type = this->_valuestruct->Type;

    if(this->_valuestruct->Type == InternalType::String)
    {
        int len1 = strlen(this->_valuestruct->Value.AsciiString), len2 = strlen(rhs._valuestruct->Value.AsciiString);
        dv._valuestruct->Value.AsciiString = new char[len1 + len2 + 1];
        strcpy(dv._valuestruct->Value.AsciiString, this->_valuestruct->Value.AsciiString);
        strcpy(dv._valuestruct->Value.AsciiString + len1, rhs._valuestruct->Value.AsciiString);
        dv._valuestruct->Value.AsciiString[len1 + len2] = '\0';
    }
    else if(this->_valuestruct->Type == InternalType::Real)
        dv._valuestruct->Value.Real = this->_valuestruct->Value.Real + rhs._valuestruct->Value.Real;
    else
        dv._valuestruct->Value.UInt64 = this->_valuestruct->Value.UInt64 + rhs._valuestruct->Value.UInt64;

    return dv;
}

DataValue DataValue::operator -(const DataValue &rhs) const
{
    if(this->_valuestruct->Type != rhs._valuestruct->Type)
        throw std::runtime_error("Cannot add DataValues with different types");

    if(this->_valuestruct->Type == InternalType::String)
        throw std::runtime_error("Cannot use '-' operator with strings");

    if(this->_valuestruct->Type == InternalType::Invalid)
        return DataValue();

    DataValue dv;
    dv._valuestruct->Type = this->_valuestruct->Type;

    if(this->_valuestruct->Type == InternalType::Real)
        dv._valuestruct->Value.Real = this->_valuestruct->Value.Real - rhs._valuestruct->Value.Real;
    else
        dv._valuestruct->Value.UInt64 = this->_valuestruct->Value.UInt64 - rhs._valuestruct->Value.UInt64;

    return dv;
}

DataValue& DataValue::operator +=(const DataValue &rhs)
{
    if(this->_valuestruct->Type != rhs._valuestruct->Type)
        throw std::runtime_error("Cannot add DataValues with different types");

    if(this->_valuestruct->Type == InternalType::Invalid)
        throw std::runtime_error("DataValue is null");

    if(this->_valuestruct->Type == InternalType::String)
    {
        int len1 = strlen(this->_valuestruct->Value.AsciiString), len2 = strlen(rhs._valuestruct->Value.AsciiString);
        const char* oldstring = this->_valuestruct->Value.AsciiString;

        this->_valuestruct->Value.AsciiString = new char[len1 + len2 + 1];
        strcpy(this->_valuestruct->Value.AsciiString, oldstring);
        strcpy(this->_valuestruct->Value.AsciiString + len1, rhs._valuestruct->Value.AsciiString);

        this->_valuestruct->Value.AsciiString[len1 + len2] = '\0';
        delete[] oldstring;
    }
    else if(this->_valuestruct->Type == InternalType::Real)
        this->_valuestruct->Value.Real += rhs._valuestruct->Value.Real;
    else
        this->_valuestruct->Value.UInt64 += rhs._valuestruct->Value.UInt64;

    return *this;
}

DataValue& DataValue::operator -=(const DataValue &rhs)
{
    if(this->_valuestruct->Type != rhs._valuestruct->Type)
        throw std::runtime_error("Cannot add DataValues with different types");

    if(this->_valuestruct->Type == InternalType::String)
        throw std::runtime_error("Cannot use '-=' operator with strings");

    if(this->_valuestruct->Type == InternalType::Invalid)
        throw std::runtime_error("DataValue is null");

    if(this->_valuestruct->Type == InternalType::Real)
        this->_valuestruct->Value.Real -= rhs._valuestruct->Value.Real;
    else
        this->_valuestruct->Value.UInt64 -= rhs._valuestruct->Value.UInt64;

    return *this;
}

DataValue& DataValue::operator =(const DataValue &rhs)
{
    LuaReference::operator =(rhs);

    this->_valuestruct = rhs._valuestruct;
    return *this;
}

} // namespace PrefLib
