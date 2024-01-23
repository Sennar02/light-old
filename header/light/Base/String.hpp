#ifndef LIGHT_BASE_STRING_HPP
#define LIGHT_BASE_STRING_HPP

#include <light/Base/math.hpp>

#include <string.h> // strlen

namespace lgh
{
    class String
    {
    public:
        /**
         *
         */
        String(const char* memory = 0, u32 length = g_max_u32);

        /**
         *
         */
        const char*
        memory() const;

        /**
         *
         */
        u32
        length() const;

        /**
         *
         */
        u32
        hash() const;

        /**
         *
         */
        char
        operator[](u32 index) const;

        /**
         *
         */
        bool
        operator==(const String& other) const;

    private:
        /**
         *
         */
        const char* m_memory;

        /**
         *
         */
        u32 m_length;

        /**
         *
         */
        u32 m_hash;
    };
} // namespace lgh

#endif // LIGHT_BASE_STRING_HPP
