#include <light/Memory/Layout/FixedLayout.hpp>

namespace lgh
{
    FixedLayout::FixedLayout()
        : m_memory {0}
        , m_length {0}
    { }

    FixedLayout::FixedLayout(BaseOrigin& origin, u32 items, u32 scale)
        : FixedLayout(origin.acquire(items * scale).item(0), items, scale)
    { }

    FixedLayout::FixedLayout(void* memory, u32 items, u32 scale)
        : m_memory {0}
        , m_length {0}
    {
        u32 length = items * scale;

        if ( memory != 0 && length != 0 ) {
            m_memory = (char*) memory;
            m_length = length;
        }
    }

    char*
    FixedLayout::memory() const
    {
        return m_memory;
    }

    u32
    FixedLayout::length(u32 scale) const
    {
        return m_length / scale;
    }

    bool
    FixedLayout::resize(u32 items, u32 scale)
    {
        return m_length == items * scale;
    }

    char&
    FixedLayout::find(u32 index, u32 scale) const
    {
        return m_memory[index * scale];
    }
} // namespace lgh
