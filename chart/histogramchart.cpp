#include "histogramchart.h"

namespace PrefLib {
namespace Chart {

HistogramChart::HistogramChart(): AbstractChart()
{
    this->_result.MaxByte = 0x00;
    this->_result.MaxCount = 0x00;
}

HistogramChart::~HistogramChart()
{

}

const ByteElaborator::CountResult &HistogramChart::result() const
{
    return this->_result;
}

void HistogramChart::elaborate(IO::DataBuffer *databuffer, uint64_t startoffset, uint64_t endoffset, volatile bool *cancontinue)
{
    ByteElaborator::countBytes(this->_result, databuffer, startoffset, endoffset, cancontinue);
}

} // namespace Chart
} // namespace PrefLib

