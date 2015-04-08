#include "segment.h"

namespace PrefLib {
namespace Disassembler {

Segment::Segment(const char *name, Segment::Type segmenttype, uint64_t startaddress, uint64_t size, uint64_t baseoffset): Block(startaddress, size)
{
    lua_State* l = LuaState::instance();

    this->push();
    this->setString("name", name);
    this->setInteger("type", segmenttype);
    this->setInteger("baseoffset", baseoffset);
    lua_pop(l, 1);
}

Segment::~Segment()
{

}

bool Segment::isCode() const
{
    return this->getInteger("type") == Segment::Code;
}

bool Segment::isData() const
{
    return this->getInteger("type") == Segment::Data;
}

const char *Segment::name() const
{
    return this->getString("name");
}

Block::Type Segment::type() const
{
    return Block::SegmentBlock;
}

} // namespace Disassembler
} // namespace PrefLib

