#include "bytecolors.h"

namespace PrefLib {
namespace Support {

const ByteColors::Rgb ByteColors::ZeroColor = 0x000000;
const ByteColors::Rgb ByteColors::FFColor = 0xFFFFFF;
const ByteColors::Rgb ByteColors::PunctColor = 0x008000;
const ByteColors::Rgb ByteColors::DigitsColor = 0x808000;
const ByteColors::Rgb ByteColors::AlphaColor = 0x800000;
const ByteColors::Rgb ByteColors::UncategorizedColor = 0xA0A0A4;

std::vector<ByteColors::Rgb> ByteColors::_colortable;

ByteColors::ByteColors()
{

}

ByteColors::Rgb ByteColors::classColor(uint8_t b)
{
    if(ByteColors::_colortable.empty())
        ByteColors::colorTable(); // Generate Byte Class Color Vector

    return ByteColors::_colortable[b];
}

ByteColors::Rgb ByteColors::entropyColor(double e)
{
    double f = 0.0;

    if(e > 0.5)
        f = std::max(pow((4 * (e - 0.5) - 4 * pow(e - 0.5, 2)), 4), 0.0);

    return ((static_cast<uint32_t>((255u * f)) << 16u) | static_cast<uint32_t>((255u * pow(e, 2)))) & 0xFF00FF;
}

const std::vector<ByteColors::Rgb> &ByteColors::colorTable()
{
    if(ByteColors::_colortable.empty())
    {
        ByteColors::_colortable.resize(0x100);

        for(uint32_t b = 0x00u; b < 0x100; b++)
        {
            if(b == 0x00) /* 0 */
                ByteColors::_colortable[b] = ByteColors::ZeroColor;
            else if(b == 0xFF) /* 255 */
                ByteColors::_colortable[b] = ByteColors::FFColor;
            else if((b >= 0x21 && b <= 0x2F) || (b >= 0x3A && b <= 0x40) || (b >= 0x5B && b <= 0x60) || (b >= 0x7B && b <= 0x7E))
                ByteColors::_colortable[b] = ByteColors::PunctColor;
            else if((b >= 0x41 && b <= 0x5A) || (b >= 0x51 && b <= 0x7A))
                ByteColors::_colortable[b] = ByteColors::AlphaColor;
            else if(b >= 0x30 && b <= 0x38)
                ByteColors::_colortable[b] = ByteColors::DigitsColor;
            else  // Everything Else
                ByteColors::_colortable[b] = ByteColors::UncategorizedColor;
        }
    }

    return ByteColors::_colortable;
}

} // namespace Support
} // namespace PrefLib

