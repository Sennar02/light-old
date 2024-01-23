#include <light/Memory/Origin/BaseOrigin.hpp>

namespace lgh
{
    BaseOrigin::BaseOrigin()
        : m_memory {0}
        , m_length {0}
    { }

    BaseOrigin::BaseOrigin(void* memory, u32 length)
        : BaseOrigin()
    {
        if ( memory != 0 && length != 0 ) {
            m_memory = (char*) memory;
            m_length = length;
        }
    }

    const char*
    BaseOrigin::memory() const
    {
        return m_memory;
    }

    u32
    BaseOrigin::length() const
    {
        return m_length;
    }

    bool
    BaseOrigin::contains(void* memory) const
    {
        char* inf = m_memory;
        char* sup = m_memory + m_length;

        if ( inf <= memory && memory < sup )
            return true;

        return false;
    }

    bool
    BaseOrigin::accepts(void* memory) const
    {
        return contains(memory);
    }
} // namespace lgh
