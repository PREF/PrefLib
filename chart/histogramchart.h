#ifndef PREFLIB_CHART_HISTOGRAMCHART_H
#define PREFLIB_CHART_HISTOGRAMCHART_H

#include <vector>
#include "../support/byteelaborator.h"
#include "abstractchart.h"

namespace PrefLib {
namespace Chart {

using namespace Support;

class HistogramChart: public virtual AbstractChart
{
    public:
        HistogramChart();
        ~HistogramChart();
        const ByteElaborator::CountResult& result() const;

    public:
        virtual void elaborate(IO::DataBuffer *databuffer, uint64_t startoffset, uint64_t endoffset);

    private:
        ByteElaborator::CountResult _result;
};

} // namespace Chart
} // namespace PrefLib

#endif // PREFLIB_CHART_HISTOGRAMCHART_H
