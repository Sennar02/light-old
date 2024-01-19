#include <light/Memory/Origin/ArenaOrigin.hpp>

namespace lgt
{
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

    Result<char*, err::Acquire>
    ArenaOrigin::acquire(u32 length, u8 align)
    {
        u32 pref = round(m_border, align);

        char* addr = m_border + pref;
        char* next = addr + length;

        if ( is_power_of_two(align) == false )
            return err::AlignmentFiasco;

        if ( length == 0 ) return err::NoByteRequested;

        if ( next <= m_memory + m_length ) {
            m_border = next;

            return (char*)
                memset(addr, 0, length);
        }

        return err::NotEnoughMemory;
    }

    Result<bool, err::Release>
    ArenaOrigin::release(void* memory)
    {
        if ( memory == 0 )
            return true;

        return err::NotMemoryParent;
    }
} // namespace lgt
