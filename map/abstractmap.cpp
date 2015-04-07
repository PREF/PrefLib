#include "abstractmap.h"

namespace PrefLib {
namespace Map {

AbstractMap::AbstractMap(): _databuffer(nullptr), _startoffset(0ul), _width(0ul)
{

}

AbstractMap::~AbstractMap()
{

}

IO::DataBuffer *AbstractMap::dataBuffer() const
{
    return this->_databuffer;
}

uint64_t AbstractMap::startOffset() const
{
    return this->_startoffset;
}

uint64_t AbstractMap::width() const
{
    return this->_width;
}

void AbstractMap::elaborate(IO::DataBuffer *databuffer, uint64_t startoffset, uint64_t width)
{
    this->_databuffer = databuffer;
    this->_startoffset = startoffset;
    this->_width = width;

    this->doElaborate();
}

} // namespace Map
} // namespace PrefLib

