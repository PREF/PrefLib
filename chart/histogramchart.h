#ifndef PREFLIB_CHART_HISTOGRAMCHART_H
#define PREFLIB_CHART_HISTOGRAMCHART_H

#include <vector>
#include "abstractchart.h"

namespace PrefLib {
namespace Chart {

class HistogramChart: public virtual AbstractChart
{
    public:
        typedef std::vector<uintmax_t> HistogramData;

    public:
        HistogramChart();
        ~HistogramChart();
        const HistogramData& data() const;
        uint8_t maxByte() const;
        uintmax_t maxCount() const;

    public:
        virtual void elaborate(IO::DataBuffer *databuffer, uint64_t startoffset, uint64_t endoffset);

    private:
        HistogramData _data;
        uint8_t _maxbyte;
        uint64_t _maxcount;
};

} // namespace Chart
} // namespace PrefLib

#endif // PREFLIB_CHART_HISTOGRAMCHART_H
