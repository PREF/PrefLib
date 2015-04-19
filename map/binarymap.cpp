#include "binarymap.h"

namespace PrefLib {
namespace Map {

BinaryMap::BinaryMap(): _mode(MapMode::Class)
{

}

BinaryMap::~BinaryMap()
{

}

void BinaryMap::doElaborate()
{
    IO::DataBuffer* databuffer = this->dataBuffer();
    uint64_t len = this->length();
    this->_data.resize(len);

    for(uint64_t i = 0, offset = this->startOffset(); offset < this->endOffset(); i++, offset++)
    {
        const Support::ByteColors::Info& info = Support::ByteColors::info(databuffer->at(offset));
        ByteData& bd = this->_data.at(i);

        if(this->_mode == MapMode::Class)
            bd.Category = info.Category;
        else // if(this->_mode == MapMode::Entropy)
            bd.Entropy = Support::Algorithm::entropy(databuffer, offset, std::min(32ul, len));
    }
}

const BinaryMap::ByteDataList& BinaryMap::data() const
{
    return this->_data;
}

BinaryMap::MapMode BinaryMap::mode() const
{
    return this->_mode;
}

void BinaryMap::setMode(BinaryMap::MapMode mode)
{
    if(this->_mode == mode)
        return;

    this->_mode = mode;
}

uint64_t BinaryMap::length() const
{
    return this->endOffset() - this->startOffset();
}

uint64_t BinaryMap::offset(const AbstractMap::Point &p) const
{
    return this->startOffset() + (p.x + (p.y * this->width()));
}

} // namespace Map
} // namespace PrefLib

