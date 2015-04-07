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
    uint64_t s = std::min(500ul, databuffer->length()), start = this->startOffset();

    this->_matrix.resize(s);

    for(uint64_t i = 0; i < s; i++)
    {
        if((start + i) > databuffer->length())
            break;

        uint64_t ioffset = start + i;
        uint8_t ib = databuffer->at(ioffset);

        this->_matrix[i].resize(s);

        for(uint64_t j = 0; j < s; j++)
        {
            uint64_t joffset = start + j;

            if(joffset > databuffer->length())
                break;

            uint8_t jb = databuffer->at(joffset);

            if(ib != jb)
            {
                this->_matrix[i][j] = 0x00;
                continue;
            }

            /* TODO: Reproduce Yellow Selection from PREF source code */
            this->_matrix[i][j] = static_cast<uint8_t>((static_cast<double>(jb) * 0.75) + 64);;
        }
    }
}

const DotPlotMap::Matrix &DotPlotMap::matrix() const
{
    return this->_matrix;
}

uint64_t DotPlotMap::length() const
{
    if(!this->_databuffer)
        return 0;

    return this->_databuffer->length();
}

uint64_t DotPlotMap::offset(const AbstractMap::Point &p) const
{
    uint64_t l = this->length();
    uint64_t s = std::min(500ul, l);

    if(p.x > s || p.y > s)
        return -1;

    uint64_t offset = this->startOffset() + (p.x + (p.y / s));

    if(offset <= l)
        return offset;

    return -1;
}

void DotPlotMap::elaborate(IO::DataBuffer *databuffer, uint64_t startoffset)
{
    AbstractMap::elaborate(databuffer, startoffset, 500);
}

} // namespace Map
} // namespace PrefLib

