#include "histogramchart.h"

namespace PrefLib {
namespace Chart {

HistogramChart::HistogramChart(): AbstractChart(), _maxbyte(0x00), _maxcount(0x00)
{

}

HistogramChart::~HistogramChart()
{

}

const HistogramChart::HistogramData &HistogramChart::data() const
{
    return this->_data;
}

uint8_t HistogramChart::maxByte() const
{
    return this->_maxbyte;
}

uintmax_t HistogramChart::maxCount() const
{
    return this->_maxcount;
}

void HistogramChart::elaborate(IO::DataBuffer *databuffer, uint64_t startoffset, uint64_t endoffset)
{
    this->_data.clear();
    this->_data.resize(0x100, 0x00);

    for(uint64_t i = startoffset; i < endoffset; i++)
    {
        uint8_t b = databuffer->at(i);
        uintmax_t& c = ++this->_data.at(b);

        if(c > this->_maxcount)
        {
            this->_maxbyte = b;
            this->_maxcount = c;
        }
    }
}

} // namespace Chart
} // namespace PrefLib

