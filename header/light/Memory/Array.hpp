#ifndef LIGHT_MEMORY_ARRAY_HPP
#define LIGHT_MEMORY_ARRAY_HPP

#include <light/Memory/define.hpp>

namespace lgt
{
    template <class Item, class Layout = FixedLayout>
    class Array
    {
    public:
        /**
         *
         */
        static const u32 s_size = sizeof(Item);

    public:
        /**
         *
         */
        template <class Origin, class... Args>
        Array(Origin& origin, u32 length, Args... args);

        /**
         *
         */
        template <class... Args>
        Array(void* memory, u32 length, Args... args);

        /**
         *
         */
        Array(const Layout& layout);

        /**
         *
         */
        u32
        length() const;

        /**
         *
         */
        bool
        resize(u32 length);

        /**
         *
         */
        Item&
        find(u32 index) const;

        /**
         *
         */
        Item&
        operator[](u32 index) const;

    protected:
        /**
         *
         */
        Layout m_layout;
    };
} // namespace lgt

#include <light/Memory/inline/Array.inl>

#endif // LIGHT_MEMORY_ARRAY_HPP
