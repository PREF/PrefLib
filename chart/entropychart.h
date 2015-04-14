#ifndef PREFLIB_CHART_ENTROPYCHART_H
#define PREFLIB_CHART_ENTROPYCHART_H

#include <vector>
#include "abstractchart.h"
#include "../support/math.h"

namespace PrefLib {
namespace Chart {

using namespace Support;

class EntropyChart : public AbstractChart
{
    public:
        typedef EntropyChart::PointT<double> EntropyPoint;
        typedef std::vector<EntropyPoint> EntropyPoints;

    public:
        EntropyChart();
        ~EntropyChart();
        const EntropyPoints& points() const;

    private:
        uint64_t calculateBlockSize(uint64_t len);

    public:
        virtual void elaborate(IO::DataBuffer *databuffer, uint64_t startoffset, uint64_t endoffset, volatile bool* cancontinue = nullptr);

    private:
        EntropyPoints _points;

    private:
        static const uint64_t NUM_POINTS;
        static const uint64_t MIN_BLOCK_SIZE;
};

} // namespace Chart
} // namespace PrefLib

#endif // PREFLIB_CHART_ENTROPYCHART_H
