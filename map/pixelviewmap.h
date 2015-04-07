#ifndef PREFLIB_MAP_PIXELVIEWMAP_H
#define PREFLIB_MAP_PIXELVIEWMAP_H

#include "../support/bytecolors.h"
#include "abstractmap.h"

namespace PrefLib {
namespace Map {

class PixelViewMap : public AbstractMap
{
    public:
        typedef std::vector<Support::ByteColors::Rgb> PixelMap;

    public:
        PixelViewMap();
        ~PixelViewMap();

    protected:
        void doElaborate();

    public:
        virtual uint64_t length() const;
        virtual uint64_t offset(const AbstractMap::Point& p) const;

    private:
        PixelMap _pixelmap;
};

} // namespace Map
} // namespace PrefLib

#endif // PREFLIB_MAP_PIXELVIEWMAP_H
