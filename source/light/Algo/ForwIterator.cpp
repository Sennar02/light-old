#include <light/Algo/ForwIterator.hpp>

namespace lgh
{
    ForwIterator::ForwIterator()
        : m_index {g_max_u32}
    { }

    bool
    ForwIterator::has_next(u32 count) const
    {
        u32 next = m_index + 1u;

        if ( next < count )
            return true;

        return false;
    }

    u32
    ForwIterator::next(u32 count)
    {
        u32 next = m_index + 1u;

        if ( next < count )
            m_index = next;

        return next;
    }

    void
    ForwIterator::reset()
    {
        m_index = g_max_u32;
    }
} // namespace lgh
