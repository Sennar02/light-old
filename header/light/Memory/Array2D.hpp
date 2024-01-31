#ifndef LIGHT_MEMORY_ARRAY_2D_HPP
#define LIGHT_MEMORY_ARRAY_2D_HPP

#include <light/Memory/Array.hpp>

namespace lgh
{
    template <class Item, class Layout = FixedLayout>
    class Array2D
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
        Array2D();

        /**
         *
         */
        template <class Origin, class... Args>
        Array2D(Origin& origin, u32 length, u32 width, Args... args);

        /**
         *
         */
        template <class... Args>
        Array2D(void* memory, u32 length, u32 width, Args... args);

        /**
         *
         */
        Array2D(const Layout& layout, u32 width);

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
        find(u32 index);

        /**
         *
         */
        const Item&
        find(u32 index) const;

        /**
         *
         */
        Item&
        find(Vec2u index);

        /**
         *
         */
        const Item&
        find(Vec2u index) const;

        /**
         *
         */
        Item&
        operator[](u32 index);

        /**
         *
         */
        const Item&
        operator[](u32 index) const;

        /**
         *
         */
        Item&
        operator[](Vec2u index);

        /**
         *
         */
        const Item&
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
} // namespace lgh

#include <light/Memory/inline/Array2D.inl>

#endif // LIGHT_MEMORY_ARRAY_2D_HPP
