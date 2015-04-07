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
        typedef uint32_t Rgb;

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
        static ByteColors::Rgb classColor(uint8_t b);
        static ByteColors::Rgb entropyColor(double e);
        static const std::vector<ByteColors::Rgb>& colorTable();

    private:
        static std::vector<ByteColors::Rgb> _colortable;
};

} // namespace Support
} // namespace PrefLib

#endif // PREFLIB_SUPPORT_BYTECOLORS_H
