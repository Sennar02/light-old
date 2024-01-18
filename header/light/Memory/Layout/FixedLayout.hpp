#ifndef LIGHT_MEMORY_LAYOUT_FIXED_LAYOUT_HPP
#define LIGHT_MEMORY_LAYOUT_FIXED_LAYOUT_HPP

#include <light/Memory/define.hpp>

namespace lgt
{
    class FixedLayout
    {
    public:
        /**
         *
         */
        FixedLayout(void* memory, u32 items, u32 scale);

        /**
         *
         */
        char*
        memory() const;

        /**
         *
         */
        u32
        length(u32 scale) const;

        /**
         *
         */
        bool
        resize(u32 items, u32 scale);

        /**
         *
         */
        char&
        find(u32 index, u32 scale) const;

    private:
        /**
         *
         */
        char* m_memory;

        /**
         *
         */
        u32 m_length;
    };
} // namespace lgt

#endif // LIGHT_MEMORY_LAYOUT_FIXED_LAYOUT_HPP
