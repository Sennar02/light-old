#include <light/Memory/Array.hpp>

namespace lgt
{
    template <class Item, class Layout>
    template <class Origin, class... Args>
    Array<Item, Layout>::Array(Origin& origin, u32 length, Args... args)
        : m_layout {origin, length, s_size, forw<Args>(args)...}
    { }

    template <class Item, class Layout>
    template <class... Args>
    Array<Item, Layout>::Array(Item memory[], u32 length, Args... args)
        : m_layout {memory, length, s_size, forw<Args>(args)...}
    { }

    template <class Item, class Layout>
    Array<Item, Layout>::Array(const Layout& layout)
        : m_layout {layout}
    { }

    template <class Item, class Layout>
    u32
    Array<Item, Layout>::length() const
    {
        return m_layout.length(s_size);
    }

    template <class Item, class Layout>
    bool
    Array<Item, Layout>::resize(u32 length)
    {
        return m_layout.resize(length, s_size);
    }

    template <class Item, class Layout>
    Item&
    Array<Item, Layout>::find(u32 index) const
    {
        return (Item&) m_layout.find(index, s_size);
    }

    template <class Item, class Layout>
    Item&
    Array<Item, Layout>::operator[](u32 index) const
    {
        return (Item&) m_layout.find(index, s_size);
    }
} // namespace lgt
