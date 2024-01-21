#include <light/Algo/ArrayList.hpp>

namespace lgt
{
    template <class Item, class Layout>
    ArrayList<Item, Layout>::ArrayList()
        : m_array {}
        , m_count {0}
    { }

    template <class Item, class Layout>
    template <class... Args>
    ArrayList<Item, Layout>::ArrayList(const Array<Item, Layout>& array, Args... args)
        : m_array {array, args...}
        , m_count {0}
    { }

    template <class Item, class Layout>
    template <class... Args>
    ArrayList<Item, Layout>::ArrayList(Args... args)
        : m_array {args...}
        , m_count {0}
    { }

    template <class Item, class Layout>
    u32
    ArrayList<Item, Layout>::size() const
    {
        return m_array.length();
    }

    template <class Item, class Layout>
    u32
    ArrayList<Item, Layout>::count() const
    {
        return m_count;
    }

    template <class Item, class Layout>
    bool
    ArrayList<Item, Layout>::is_full() const
    {
        return m_count == m_array.length();
    }

    template <class Item, class Layout>
    bool
    ArrayList<Item, Layout>::is_empty() const
    {
        return m_count == 0;
    }

    template <class Item, class Layout>
    Result<bool, fail::Insert>
    ArrayList<Item, Layout>::insert(const Item& item, u32 index)
    {
        u32 place = min(m_count, index);

        if ( is_full() ) return fail::NotEnoughSpace;

        if ( place < m_count ) {
            for ( u32 i = m_count; i > place; i-- )
                m_array[i] = move(m_array[i - 1u]);
        }

        ctor(m_array[place], item);
        m_count += 1u;

        return true;
    }

    template <class Item, class Layout>
    Result<Item, fail::Remove>
    ArrayList<Item, Layout>::remove(u32 index)
    {
        u32  place = min(m_count - 1u, index);
        Item item  = m_array[place];

        if ( is_empty() ) return fail::UnknownElement;

        m_count -= 1u;

        if ( place < m_count ) {
            for ( u32 i = place; i < m_count; i++ )
                m_array[i] = move(m_array[i + 1u]);
        }

        return item;
    }

    template <class Item, class Layout>
    template <class Iter, class Func>
    ArrayList<Item, Layout>&
    ArrayList<Item, Layout>::for_each(Iter& iter, Func func)
    {
        while ( iter.next() )
            func(iter.item(), iter.index());

        return *this;
    }

    template <class Item, class Layout>
    template <class Func>
    ArrayList<Item, Layout>&
    ArrayList<Item, Layout>::for_each(Func func)
    {
        ArrayListForwIter iter = {*this};

        while ( iter.next() )
            func(iter.item(), iter.index());

        return *this;
    }

    template <class Item, class Layout>
    ArrayList<Item, Layout>&
    ArrayList<Item, Layout>::clear()
    {
        m_count = 0;

        return *this;
    }

    template <class Item, class Layout>
    Option<Item&>
    ArrayList<Item, Layout>::find(u32 index) const
    {
        if ( index < m_array.length() )
            return m_array[index];

        return true;
    }

    template <class Item, class Layout>
    Option<Item&>
    ArrayList<Item, Layout>::operator[](u32 index) const
    {
        return find(index);
    }

    template <class Item, class Layout>
    const Array<Item, Layout>&
    ArrayList<Item, Layout>::array() const
    {
        return m_array;
    }

    template <class Item, class Layout>
    ArrayListForwIter<Item, Layout>::ArrayListForwIter(const List& list)
        : m_list {list}
        , m_index {g_max_u32}
    { }

    template <class Item, class Layout>
    u32
    ArrayListForwIter<Item, Layout>::index() const
    {
        return m_index;
    }

    template <class Item, class Layout>
    Item&
    ArrayListForwIter<Item, Layout>::item()
    {
        return m_list.array()[m_index];
    }

    template <class Item, class Layout>
    const Item&
    ArrayListForwIter<Item, Layout>::item() const
    {
        return m_list.array()[m_index];
    }

    template <class Item, class Layout>
    bool
    ArrayListForwIter<Item, Layout>::has_next() const
    {
        u32 next = m_index + 1u;

        if ( next < m_list.count() )
            return true;

        return false;
    }

    template <class Item, class Layout>
    bool
    ArrayListForwIter<Item, Layout>::next()
    {
        u32 next = m_index + 1u;

        if ( next < m_list.count() )
            m_index = next;

        return m_index == next;
    }

    template <class Item, class Layout>
    void
    ArrayListForwIter<Item, Layout>::reset()
    {
        m_index = g_max_u32;
    }
} // namespace lgt
