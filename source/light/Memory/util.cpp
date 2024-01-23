#include <light/Memory/util.hpp>

namespace lgh
{
    u32
    round(void* memory, u8 align, u32 extra)
    {
        upt value = (upt) memory + extra;
        upt error = value & (align - 1u);

        if ( error != 0 )
            extra += align - error;

        return extra;
    }

    bool
    is_power_of_two(u8 align)
    {
        u8 value = align & (align - 1u);

        return value == 0 &&
               align != 0;
    }
} // namespace lgh
