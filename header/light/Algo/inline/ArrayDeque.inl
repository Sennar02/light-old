#include <light/Algo/ArrayDeque.hpp>

namespace lgt
{
    template <class Item, class Layout>
    ArrayDeque<Item, Layout>::ArrayDeque()
        : m_array {}
        , m_delta {0}
        , m_count {0}
    { }

    template <class Item, class Layout>
    template <class... Args>
    ArrayDeque<Item, Layout>::ArrayDeque(const Array<Item, Layout>& array, Args... args)
        : m_array {array, args...}
        , m_delta {0}
        , m_count {0}
    { }

    template <class Item, class Layout>
    template <class... Args>
    ArrayDeque<Item, Layout>::ArrayDeque(Args... args)
        : m_array {args...}
        , m_delta {0}
        , m_count {0}
    { }

    template <class Item, class Layout>
    u32
    ArrayDeque<Item, Layout>::size() const
    {
        return m_array.length();
    }

    template <class Item, class Layout>
    u32
    ArrayDeque<Item, Layout>::count() const
    {
        return m_count;
    }

    template <class Item, class Layout>
    bool
    ArrayDeque<Item, Layout>::is_full() const
    {
        return m_count == m_array.length();
    }

    template <class Item, class Layout>
    bool
    ArrayDeque<Item, Layout>::is_empty() const
    {
        return m_count == 0;
    }

    template <class Item, class Layout>
    template <class Iter, class Func>
    ArrayDeque<Item, Layout>&
    ArrayDeque<Item, Layout>::for_each(Iter& iter, Func func)
    {
        while ( iter.next() )
            func(iter.item(), iter.index());

        return *this;
    }

    template <class Item, class Layout>
    template <class Func>
    ArrayDeque<Item, Layout>&
    ArrayDeque<Item, Layout>::for_each(Func func)
    {
        ArrayDequeForwIter iter = {*this};

        while ( iter.next() )
            func(iter.item(), iter.index());

        return *this;
    }

    template <class Item, class Layout>
    Result<bool, fail::Insert>
    ArrayDeque<Item, Layout>::insert(const Item& item)
    {
        u32 index = next(m_delta, m_count);

        if ( is_full() ) return fail::NotEnoughSpace;

        ctor(m_array[index], item);
        m_count += 1u;

        return true;
    }

    template <class Item, class Layout>
    Result<Item, fail::Remove>
    ArrayDeque<Item, Layout>::remove(algo::DequeSide side)
    {
        u32 index = m_delta;

        if ( is_empty() ) return fail::UnknownElement;

        if ( side == algo::Head )
            index = m_count - 1u;
        else
            m_delta = next(index);

        m_count -= 1u;

        return m_array[index];
    }

    template <class Item, class Layout>
    ArrayDeque<Item, Layout>&
    ArrayDeque<Item, Layout>::clear()
    {
        m_count = 0;
        m_delta = 0;

        return *this;
    }

    template <class Item, class Layout>
    Option<Item&>
    ArrayDeque<Item, Layout>::find(u32 index) const
    {
        if ( index < m_count )
            return m_array[next(m_delta, index)];

        return true;
    }

    template <class Item, class Layout>
    Item&
    ArrayDeque<Item, Layout>::operator[](u32 index) const
    {
        return m_array[next(m_delta, index)];
    }

    template <class Item, class Layout>
    const Array<Item, Layout>&
    ArrayDeque<Item, Layout>::array() const
    {
        return m_array;
    }

    template <class Item, class Layout>
    u32
    ArrayDeque<Item, Layout>::next(u32 code, u32 step) const
    {
        u32 length = m_array.length();

        if ( length != 0 )
            return (code + step) % length;

        return length;
    }

    template <class Item, class Layout>
    ArrayDequeForwIter<Item, Layout>::ArrayDequeForwIter(const Deque& deque)
        : m_deque {deque}
        , m_index {g_max_u32}
    { }

    template <class Item, class Layout>
    u32
    ArrayDequeForwIter<Item, Layout>::index() const
    {
        return m_index;
    }

    template <class Item, class Layout>
    Item&
    ArrayDequeForwIter<Item, Layout>::item()
    {
        return m_deque.array()[m_index];
    }

    template <class Item, class Layout>
    const Item&
    ArrayDequeForwIter<Item, Layout>::item() const
    {
        return m_deque.array()[m_index];
    }

    template <class Item, class Layout>
    bool
    ArrayDequeForwIter<Item, Layout>::has_next() const
    {
        u32 next = m_index + 1u;

        if ( next < m_deque.count() )
            return true;

        return false;
    }

    template <class Item, class Layout>
    bool
    ArrayDequeForwIter<Item, Layout>::next()
    {
        u32 next = m_index + 1u;

        if ( next < m_deque.count() )
            m_index = next;

        return m_index == next;
    }

    template <class Item, class Layout>
    void
    ArrayDequeForwIter<Item, Layout>::reset()
    {
        m_index = g_max_u32;
    }
} // namespace lgt
