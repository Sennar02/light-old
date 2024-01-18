#ifndef LIGHT_MEMORY_UTIL_HPP
#define LIGHT_MEMORY_UTIL_HPP

#include <light/Memory/define.hpp>

namespace lgt
{
    /**
     *
     */
    u32
    round(void* memory, u8 align, u32 extra = 0);

    /**
     *
     */
    bool
    is_power_of_two(u8 align);
} // namespace lgt

#endif // LIGHT_MEMORY_UTIL_HPP
