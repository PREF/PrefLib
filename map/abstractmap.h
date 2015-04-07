#ifndef PREFLIB_MAP_ABSTRACTMAP_H
#define PREFLIB_MAP_ABSTRACTMAP_H

#include <cstdint>
#include "../io/databuffer.h"

namespace PrefLib {
namespace Map {

class AbstractMap
{
    public:
        struct Point { uintmax_t x; uintmax_t y; };

    public:
        AbstractMap();
        ~AbstractMap();

    protected:
        virtual void doElaborate() = 0;

    public:
        IO::DataBuffer* dataBuffer() const;
        uint64_t startOffset() const;
        uint64_t width() const;
        virtual uint64_t length() const = 0;
        virtual uint64_t offset(const AbstractMap::Point& p) const = 0;
        void elaborate(IO::DataBuffer* databuffer, uint64_t startoffset, uint64_t width);

    protected:
        IO::DataBuffer* _databuffer;
        uint64_t _startoffset;
        uint64_t _width;
};

} // namespace Map
} // namespace PrefLib

#endif // PREFLIB_MAP_ABSTRACTMAP_H
