#ifndef LIGHT_MEMORY_UTIL_HPP
#define LIGHT_MEMORY_UTIL_HPP

#include <light/Memory/define.hpp>

namespace lgh
{
    template <class Origin>
    char*
    acquire(Origin& origin, u32 length, u8 align = g_len_u32);

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
} // namespace lgh

#include <light/Memory/inline/util.inl>

#endif // LIGHT_MEMORY_UTIL_HPP
