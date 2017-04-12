#include "dotplotmap.h"

namespace PrefLib {
namespace Map {

DotPlotMap::DotPlotMap(): AbstractMap()
{

}

DotPlotMap::~DotPlotMap()
{

}

void DotPlotMap::doElaborate()
{
    IO::DataBuffer* databuffer = this->dataBuffer();
    uint64_t size = this->width(), start = this->startOffset();

    this->_dotmap.resize(pow(size, 2));

    for(uint64_t i = 0; i < size; i++)
    {
        if((start + i) > databuffer->size())
            break;

        uint64_t ioffset = start + i;
        uint8_t ib = databuffer->at(ioffset);

        for(uint64_t j = 0; j < size; j++)
        {
            uint64_t joffset = start + j;

            if(joffset > databuffer->size())
                break;

            uint8_t jb = databuffer->at(joffset);

            if(ib != jb)
            {
                this->_dotmap[i + j * size] = 0x00;
                continue;
            }

            /* TODO: Reproduce Yellow Selection from PREF source code */
            this->_dotmap[i + j * size] = static_cast<uint8_t>((static_cast<double>(jb) * 0.75) + 64);
        }
    }
}

const DotPlotMap::DotMap &DotPlotMap::dotPlot() const
{
    return this->_dotmap;
}

uint64_t DotPlotMap::length() const
{
    if(!this->_databuffer)
        return 0;

    return this->_databuffer->size();
}

uint64_t DotPlotMap::offset(const AbstractMap::Point &p) const
{
    uint64_t l = this->length();
    uint64_t s = std::min(uint64_t(500), l);

    if(p.x > s || p.y > s)
        return -1;

    uint64_t offset = this->startOffset() + (p.x + (p.y / s));

    if(offset <= l)
        return offset;

    return -1;
}

void DotPlotMap::elaborate(IO::DataBuffer *databuffer, uint64_t startoffset)
{
    AbstractMap::elaborate(databuffer, startoffset, databuffer->size(), std::min(uint64_t(500), databuffer->size() - startoffset));
}

} // namespace Map
} // namespace PrefLib

