#include "abstractchart.h"

namespace PrefLib {
namespace Chart {

AbstractChart::AbstractChart()
{

}

AbstractChart::~AbstractChart()
{

}

void AbstractChart::elaborate(IO::DataBuffer *databuffer, uint64_t startoffset)
{
    this->elaborate(databuffer, startoffset, databuffer->length());
}

void AbstractChart::elaborate(IO::DataBuffer *databuffer)
{
    this->elaborate(databuffer, 0);
}

} // namespace Chart
} // namespace PrefLib

