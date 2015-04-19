#include "entropychart.h"

namespace PrefLib {
namespace Chart {

const uint64_t EntropyChart::NUM_POINTS = 2048ul;
const uint64_t EntropyChart::MIN_BLOCK_SIZE = 32ul;

EntropyChart::EntropyChart()
{

}

EntropyChart::~EntropyChart()
{

}

const EntropyChart::EntropyPoints &EntropyChart::points() const
{
    return this->_points;
}

uint64_t EntropyChart::calculateBlockSize(uint64_t len)
{
    if(len < EntropyChart::MIN_BLOCK_SIZE)
        return 0;

    uint64_t blocksize = 0, numpoints = EntropyChart::NUM_POINTS, size = len / numpoints;

    while(size < EntropyChart::MIN_BLOCK_SIZE)
    {
        numpoints /= 2u;
        size = len / numpoints;
    }

    for(uint64_t i = 0; blocksize < size; i++)
    {
        uint64_t bs = (1u << i);

        if(bs > size)
            break;

        blocksize = bs;
    }

    this->_points.clear();
    this->_points.reserve(numpoints);
    return blocksize;
}

void EntropyChart::elaborate(IO::DataBuffer *databuffer, uint64_t startoffset, uint64_t endoffset, volatile bool *cancontinue)
{
    uint64_t len = endoffset - startoffset, blocksize = this->calculateBlockSize(len);

    if(!blocksize)
        return;

    for(uint64_t i = 0; i < len; i += blocksize)
    {
        if(cancontinue && !(*cancontinue))
            break;

        double e = Algorithm::entropy(databuffer, i, blocksize, cancontinue);
        this->_points.push_back({ static_cast<double>(i), e });
    }
}

} // namespace Chart
} // namespace PrefLib

