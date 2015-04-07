#ifndef PREFLIB_MAP_DOTPLOTMAP_H
#define PREFLIB_MAP_DOTPLOTMAP_H

#include <vector>
#include <cstdint>
#include "abstractmap.h"

namespace PrefLib {
namespace Map {

class DotPlotMap : public AbstractMap
{
    public:
        typedef std::vector<uint32_t> Row;
        typedef std::vector<DotPlotMap::Row> Matrix;

    public:
        DotPlotMap();
        ~DotPlotMap();

    protected:
        virtual void doElaborate();

    public:
        const DotPlotMap::Matrix& matrix() const;
        virtual uint64_t length() const;
        virtual uint64_t offset(const Point &p) const;
        void elaborate(IO::DataBuffer *databuffer, uint64_t startoffset);

    private:
        Matrix _matrix;
};

} // namespace Map
} // namespace PrefLib

#endif // PREFLIB_MAP_DOTPLOTMAP_H
