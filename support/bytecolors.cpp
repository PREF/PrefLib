#include "bytecolors.h"

namespace PrefLib {
namespace Support {

const ByteColors::Rgb ByteColors::ZeroColor = 0x000000;
const ByteColors::Rgb ByteColors::FFColor = 0xFFFFFF;
const ByteColors::Rgb ByteColors::PunctColor = 0x008000;
const ByteColors::Rgb ByteColors::DigitsColor = 0x808000;
const ByteColors::Rgb ByteColors::AlphaColor = 0x800000;
const ByteColors::Rgb ByteColors::UncategorizedColor = 0xA0A0A4;

std::vector<ByteColors::Info> ByteColors::_colortable;

ByteColors::ByteColors()
{

}

const ByteColors::Info &ByteColors::info(uint8_t b)
{
    if(ByteColors::_colortable.empty())
        ByteColors::colorTable(); // Generate Byte Class Color Vector

    return ByteColors::_colortable.at(b);
}

ByteColors::Rgb ByteColors::entropyColor(double e)
{
    double f = 0.0;

    if(e > 0.5)
        f = std::max(pow((4 * (e - 0.5) - 4 * pow(e - 0.5, 2)), 4), 0.0);

    return ((static_cast<uint32_t>((255u * f)) << 16u) | static_cast<uint32_t>((255u * pow(e, 2)))) & 0xFF00FF;
}

ByteColors::Rgb ByteColors::categoryColor(ByteColors::Category c)
{
    switch(c)
    {
        case Category::Zero:
            return ByteColors::ZeroColor;

        case Category::FF:
            return ByteColors::FFColor;

        case Category::Punct:
            return ByteColors::PunctColor;

        case Category::Alpha:
            return ByteColors::AlphaColor;

        case Category::Digits:
            return ByteColors::DigitsColor;

        default:
            break;
    }

    return ByteColors::UncategorizedColor;
}

const std::vector<ByteColors::Info>& ByteColors::colorTable()
{
    if(ByteColors::_colortable.empty())
    {
        ByteColors::_colortable.resize(0x100);

        for(uint32_t b = 0x00u; b < 0x100; b++)
        {
            if(b == 0x00) /* 0 */
                ByteColors::_colortable[b] = { Category::Zero, ByteColors::ZeroColor };
            else if(b == 0xFF) /* 255 */
                ByteColors::_colortable[b] = { Category::FF, ByteColors::FFColor };
            else if((b >= 0x21 && b <= 0x2F) || (b >= 0x3A && b <= 0x40) || (b >= 0x5B && b <= 0x60) || (b >= 0x7B && b <= 0x7E))
                ByteColors::_colortable[b] = { Category::Punct, ByteColors::PunctColor };
            else if((b >= 0x41 && b <= 0x5A) || (b >= 0x51 && b <= 0x7A))
                ByteColors::_colortable[b] = { Category::Alpha, ByteColors::AlphaColor };
            else if(b >= 0x30 && b <= 0x38)
                ByteColors::_colortable[b] = { Category::Digits, ByteColors::DigitsColor };
            else  // Everything Else
                ByteColors::_colortable[b] = { Category::Uncategorized, ByteColors::UncategorizedColor };
        }
    }

    return ByteColors::_colortable;
}

} // namespace Support
} // namespace PrefLib

