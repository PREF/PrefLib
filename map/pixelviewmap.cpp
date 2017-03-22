#include "pixelviewmap.h"

namespace PrefLib {
namespace Map {

PixelViewMap::PixelViewMap(): AbstractMap()
{

}

PixelViewMap::~PixelViewMap()
{

}

void PixelViewMap::doElaborate()
{
    IO::DataBuffer* databuffer = this->dataBuffer();
    uint64_t height = this->length() / this->width();
    this->_pixelmap.resize(std::min(databuffer->size(), this->_width * height));

    for(uint64_t i = 0, offset = this->startOffset(); i < this->_pixelmap.size(); i++, offset++)
        this->_pixelmap[i] = Support::ByteColors::info(databuffer->at(offset)).Color;
}

uint64_t PixelViewMap::length() const
{
    IO::DataBuffer* databuffer = this->dataBuffer();

    if(!databuffer)
        return 0;

    return databuffer->size() - this->startOffset();
}

uint64_t PixelViewMap::offset(const AbstractMap::Point &p) const
{
    IO::DataBuffer* databuffer = this->dataBuffer();
    uint64_t offset = this->startOffset() + (p.x + (p.y * this->width()));

    if(offset <= databuffer->size())
        return offset;

    return -1;
}

} // namespace Map
} // namespace PrefLib

