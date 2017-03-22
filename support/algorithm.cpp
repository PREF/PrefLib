#include "algorithm.h"

#define logn(n, base) (log(n) / log(base))

namespace PrefLib {
namespace Support {

Algorithm::Algorithm()
{

}

Algorithm::~Algorithm()
{

}

uint64_t Algorithm::rebase(uint64_t address, uint64_t oldbaseaddress, uint64_t newbaseaddress)
{
    return (address - oldbaseaddress) + newbaseaddress;
}

double Algorithm::entropy(const ByteElaborator::CountResult& cr, uint64_t size)
{
    double e = 0.0;
    uint64_t base = std::min(size, 256ul);

    for(uint64_t i = 0; i < cr.Counts.size(); i++)
    {
        const uintmax_t& c = cr.Counts.at(i);

        if(!c)
            continue;

        double freq = static_cast<double>(c) / static_cast<double>(size);
        e += freq * logn(freq, base);
    }

    return -e;
}

double Algorithm::entropy(IO::DataBuffer *databuffer, uint64_t startoffset, uint64_t size, volatile bool *cancontinue)
{
    ByteElaborator::CountResult cr;
    ByteElaborator::countBytes(cr, databuffer, startoffset, startoffset + size, cancontinue);
    return Algorithm::entropy(cr, size);
}

double Algorithm::entropy(IO::DataBuffer *databuffer, uint64_t size, volatile bool *cancontinue)
{
    return Algorithm::entropy(databuffer, 0, size, cancontinue);
}

double Algorithm::entropy(IO::DataBuffer *databuffer, volatile bool *cancontinue)
{
    return Algorithm::entropy(databuffer, databuffer->length(), cancontinue);
}

} // namespace Support
} // namespace PrefLib

