#ifndef PREFLIB_MAP_BINARYMAP_H
#define PREFLIB_MAP_BINARYMAP_H

#include "abstractmap.h"
#include "../support/bytecolors.h"
#include "../support/algorithm.h"

namespace PrefLib {
namespace Map {

class BinaryMap : public AbstractMap
{
    public:
        union ByteData { Support::ByteColors::Category Category; double Entropy; };
        typedef std::vector<ByteData> ByteDataList;
        enum MapMode { Class, Entropy };

    public:
        BinaryMap();
        ~BinaryMap();

    protected:
        virtual void doElaborate();

    public:
        const ByteDataList& data() const;
        MapMode mode() const;
        void setMode(MapMode mode);
        virtual uint64_t length() const;
        virtual uint64_t offset(const AbstractMap::Point& p) const;

    private:
        MapMode _mode;
        ByteDataList _data;
};

} // namespace Map
} // namespace PrefLib

#endif // PREFLIB_MAP_BINARYMAP_H
