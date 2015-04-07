#ifndef PREFLIB_CHART_ABSTRACTCHART_H
#define PREFLIB_CHART_ABSTRACTCHART_H

#include "../io/databuffer.h"

namespace PrefLib {
namespace Chart {

class AbstractChart
{
    public:
        template<typename T> struct PointT { T x; T y; };

    public:
        AbstractChart();
        ~AbstractChart();

    public:
        virtual void elaborate(IO::DataBuffer* databuffer, uint64_t startoffset, uint64_t endoffset) = 0;
        virtual void elaborate(IO::DataBuffer *databuffer, uint64_t startoffset);
        virtual void elaborate(IO::DataBuffer *databuffer);
};

} // namespace Chart
} // namespace PrefLib

#endif // PREFLIB_CHART_ABSTRACTCHART_H
