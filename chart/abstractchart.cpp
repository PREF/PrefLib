#include "abstractchart.h"

namespace PrefLib {
namespace Chart {

AbstractChart::AbstractChart()
{

}

AbstractChart::~AbstractChart()
{

}

void AbstractChart::elaborate(IO::DataBuffer *databuffer, uint64_t startoffset, volatile bool* cancontinue)
{
    this->elaborate(databuffer, startoffset, databuffer->length(), cancontinue);
}

void AbstractChart::elaborate(IO::DataBuffer *databuffer, volatile bool *cancontinue)
{
    this->elaborate(databuffer, 0, cancontinue);
}

} // namespace Chart
} // namespace PrefLib

