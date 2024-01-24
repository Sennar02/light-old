#include <light/Algo/BackIterator.hpp>

namespace lgh
{
    BackIterator::BackIterator()
        : m_index {g_max_u32}
    { }

    bool
    BackIterator::has_next(u32 count) const
    {
        u32 next = m_index + 1u;

        if ( next < count )
            return true;

        return false;
    }

    u32
    BackIterator::next(u32 count)
    {
        u32 next = m_index + 1u;

        if ( next < count )
            m_index = next;

        return count - next - 1u;
    }

    void
    BackIterator::reset()
    {
        m_index = g_max_u32;
    }
} // namespace lgh
