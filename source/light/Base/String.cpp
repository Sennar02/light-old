#include <light/Base/String.hpp>

namespace lgh
{
    String::String(const char* memory, u32 length)
        : m_memory {""}
        , m_length {0}
        , m_hash {0}
    {
        if ( memory != 0 && length != 0 ) {
            if ( length == g_max_u32 )
                length = strlen(memory);

            m_memory = memory;
            m_length = length;
        }

        m_hash = Hash<const char*>::code(m_memory);
    }

    const char*
    String::memory() const
    {
        return m_memory;
    }

    u32
    String::length() const
    {
        return m_length;
    }

    u32
    String::hash() const
    {
        return m_hash;
    }

    char
    String::operator[](u32 index) const
    {
        if ( index < m_length )
            return m_memory[index];

        return 0;
    }

    bool
    String::operator==(const String& other) const
    {
        if ( m_length != other.m_length )
            return false;

        for ( u32 i = 0; i < m_length; i++ ) {
            if ( m_memory[i] != other.m_memory[i] )
                return false;
        }

        return true;
    }
} // namespace lgh
