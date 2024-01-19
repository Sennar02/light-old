#include <light/Memory/Array2d.hpp>

namespace lgt
{
    template <class Item, class Layout>
    template <class Origin, class... Args>
    Array2d<Item, Layout>::Array2d(Origin& origin, u32 length, u32 width, Args... args)
        : Array2d(Layout {origin, length, width, args...}, width)
    { }

    template <class Item, class Layout>
    template <class... Args>
    Array2d<Item, Layout>::Array2d(void* memory, u32 length, u32 width, Args... args)
        : Array2d(Layout {memory, length, width, args...}, width)
    { }

    template <class Item, class Layout>
    Array2d<Item, Layout>::Array2d(const Layout& layout, u32 width)
        : Array<Item, Layout>(layout)
        , m_width {0}
        , m_height {0}
    {
        auto& self   = *(Array<Item, Layout>*) this;
        u32   length = self.length();

        if ( length != 0 && width != 0 ) {
            m_width  = width;
            m_height = length / width;
        }
    }

    template <class Item, class Layout>
    u32
    Array2d<Item, Layout>::width() const
    {
        return m_width;
    }

    template <class Item, class Layout>
    u32
    Array2d<Item, Layout>::height() const
    {
        return m_width;
    }

    template <class Item, class Layout>
    bool
    Array2d<Item, Layout>::resize(u32 length, u32 width)
    {
        auto& self = *(Array<Item, Layout>*) this;

        if ( self.resize(length) == false )
            return false;

        length = self.length();

        if ( length != 0 && width != 0 ) {
            m_width  = width;
            m_height = length / width;

            return true;
        }

        return false;
    }

    template <class Item, class Layout>
    Item&
    Array2d<Item, Layout>::find(u32 index) const
    {
        auto& self = *(Array<Item, Layout>*) this;

        return self.find(index);
    }

    template <class Item, class Layout>
    Item&
    Array2d<Item, Layout>::find(Vec2u index) const
    {
        auto& self  = *(Array<Item, Layout>*) this;
        u32   value = index[1] * m_width + index[0];

        return self.find(value);
    }

    template <class Item, class Layout>
    Item&
    Array2d<Item, Layout>::operator[](u32 index) const
    {
        auto& self = *(Array<Item, Layout>*) this;

        return self.find(index);
    }

    template <class Item, class Layout>
    Item&
    Array2d<Item, Layout>::operator[](Vec2u index) const
    {
        auto& self  = *(Array<Item, Layout>*) this;
        u32   value = index[1] * m_width + index[0];

        return self.find(value);
    }
} // namespace lgt
