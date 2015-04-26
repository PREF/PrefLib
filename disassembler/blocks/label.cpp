#include "label.h"

namespace PrefLib {
namespace Disassembler {

Label::Label(uint64_t startaddress, lua_State* thread): Block(startaddress, 0, thread)
{

}

Block::Type Label::type() const
{
    return Block::LabelBlock;
}

} // namespace Disassembler
} // namespace PrefLib

