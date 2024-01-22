#include <light/Memory/Origin/ArenaOrigin.hpp>

namespace lgt
{
    ArenaOrigin g_origin = {calloc(1u, g_KiB * 16u), g_KiB * 16u};

    ArenaOrigin::ArenaOrigin()
        : BaseOrigin()
        , m_border {0}
    { }

    ArenaOrigin::ArenaOrigin(void* memory, u32 length)
        : BaseOrigin(memory, length)
        , m_border {0}
    {
        reset();
    }

    u32
    ArenaOrigin::assures(u8 align) const
    {
        u32 dist = m_border - m_memory;
        u32 diff = m_length - dist;

        u32 pref = round(m_border, align);

        if ( is_power_of_two(align) == false )
            return 0;

        return diff - pref;
    }

    void
    ArenaOrigin::reset()
    {
        m_border = m_memory;

        if ( m_memory != 0 )
            memset(m_memory, 0, m_length);
    }

    Result<char*, fail::Acquire>
    ArenaOrigin::acquire(u32 length, u8 align)
    {
        u32 pref = round(m_border, align);

        char* addr = m_border + pref;
        char* next = addr + length;

        if ( is_power_of_two(align) == false )
            return fail::AlignmentFiasco;

        if ( length == 0 ) return fail::NoByteRequested;

        if ( next <= m_memory + m_length ) {
            m_border = next;

            return (char*)
                memset(addr, 0, length);
        }

        return fail::NotEnoughMemory;
    }

    Result<bool, fail::Release>
    ArenaOrigin::release(void* memory)
    {
        if ( memory == 0 )
            return true;

        return fail::NotMemoryParent;
    }
} // namespace lgt
