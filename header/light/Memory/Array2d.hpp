#ifndef LIGHT_MEMORY_ARRAY_2D_HPP
#define LIGHT_MEMORY_ARRAY_2D_HPP

#include <light/Memory/Array.hpp>

namespace lgt
{
    template <class Item, class Layout = FixedLayout>
    class Array2d
        : public Array<Item, Layout>
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
        Array2d(Origin& origin, u32 length, u32 width, Args... args);

        /**
         *
         */
        template <class... Args>
        Array2d(void* memory, u32 length, u32 width, Args... args);

        /**
         *
         */
        Array2d(const Layout& layout, u32 width);

        /**
         *
         */
        u32
        width() const;

        /**
         *
         */
        u32
        height() const;

        /**
         *
         */
        bool
        resize(u32 length, u32 width = 0);

        /**
         *
         */
        Item&
        find(u32 index) const;

        /**
         *
         */
        Item&
        find(Vec2u index) const;

        /**
         *
         */
        Item&
        operator[](u32 index) const;

        /**
         *
         */
        Item&
        operator[](Vec2u index) const;

    protected:
        /**
         *
         */
        u32 m_width;

        /**
         *
         */
        u32 m_height;
    };
} // namespace lgt

#include <light/Memory/inline/Array2d.inl>

#endif // LIGHT_MEMORY_ARRAY_2D_HPP
