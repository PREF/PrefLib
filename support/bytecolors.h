#ifndef PREFLIB_SUPPORT_BYTECOLORS_H
#define PREFLIB_SUPPORT_BYTECOLORS_H

#include <vector>
#include <cstdint>
#include <algorithm>

namespace PrefLib {
namespace Support {

class ByteColors
{
    public:
        enum Category { Zero, FF, Punct, Digits, Alpha, Uncategorized };
        typedef uint32_t Rgb;
        struct Info { ByteColors::Category Category; ByteColors::Rgb Color; };

    public:
        static const ByteColors::Rgb ZeroColor;
        static const ByteColors::Rgb FFColor;
        static const ByteColors::Rgb PunctColor;
        static const ByteColors::Rgb DigitsColor;
        static const ByteColors::Rgb AlphaColor;
        static const ByteColors::Rgb UncategorizedColor;

    private:
        ByteColors();

    public:
        static const ByteColors::Info& info(uint8_t b);
        static ByteColors::Rgb entropyColor(double e);
        static ByteColors::Rgb categoryColor(ByteColors::Category c);
        static const std::vector<Info>& colorTable();

    private:
        static std::vector<ByteColors::Info> _colortable;
};

} // namespace Support
} // namespace PrefLib

#endif // PREFLIB_SUPPORT_BYTECOLORS_H
