#include <light/Algo/ArrayDeque.hpp>

namespace lgh
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
    ArrayDeque<Item, Layout>::for_each(Iter iter, Func func)
    {
        u32   index = 0;
        Item* item  = 0;

        if ( is_empty() ) return *this;

        while ( iter.has_next(m_count) ) {
            index = next(m_delta, iter.next(m_count));
            item  = &m_array[index];

            func(*item, index);
        }

        return *this;
    }

    template <class Item, class Layout>
    template <class Iter, class Func>
    const ArrayDeque<Item, Layout>&
    ArrayDeque<Item, Layout>::for_each(Iter iter, Func func) const
    {
        u32         index = 0;
        const Item* item  = 0;

        if ( is_empty() ) return *this;

        while ( iter.has_next(m_count) ) {
            index = next(m_delta, iter.next(m_count));
            item  = &m_array[index];

            func(*item, index);
        }

        return *this;
    }

    template <class Item, class Layout>
    template <class Func>
    ArrayDeque<Item, Layout>&
    ArrayDeque<Item, Layout>::for_each(Func func)
    {
        return for_each(ForwIterator {}, func);
    }

    template <class Item, class Layout>
    template <class Func>
    const ArrayDeque<Item, Layout>&
    ArrayDeque<Item, Layout>::for_each(Func func) const
    {
        return for_each(ForwIterator {}, func);
    }

    template <class Item, class Layout>
    template <class... Args>
    bool
    ArrayDeque<Item, Layout>::build(const Array<Item, Layout>& array, Args... args)
    {
        if ( reset() == false )
            return false;

        ctor(m_array, array, args...);

        return true;
    }

    template <class Item, class Layout>
    template <class... Args>
    bool
    ArrayDeque<Item, Layout>::build(Args... args)
    {
        if ( reset() == false )
            return false;

        ctor(m_array, args...);

        return true;
    }

    template <class Item, class Layout>
    bool
    ArrayDeque<Item, Layout>::reset()
    {
        bool result = m_array.resize(0);

        if ( result ) {
            m_delta = 0;
            m_count = 0;
        }

        return result;
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

        if ( side == algo::Tail )
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
    Item*
    ArrayDeque<Item, Layout>::search(u32 index)
    {
        if ( index < m_count )
            return &m_array[next(m_delta, index)];

        return 0;
    }

    template <class Item, class Layout>
    const Item*
    ArrayDeque<Item, Layout>::search(u32 index) const
    {
        if ( index < m_count )
            return &m_array[next(m_delta, index)];

        return 0;
    }

    template <class Item, class Layout>
    Item&
    ArrayDeque<Item, Layout>::find(u32 index, Item& fail)
    {
        if ( index < m_count )
            return m_array[next(m_delta, index)];

        return fail;
    }

    template <class Item, class Layout>
    const Item&
    ArrayDeque<Item, Layout>::find(u32 index, const Item& fail) const
    {
        if ( index < m_count )
            return m_array[next(m_delta, index)];

        return fail;
    }

    template <class Item, class Layout>
    Item&
    ArrayDeque<Item, Layout>::operator[](u32 index)
    {
        return *search(index);
    }

    template <class Item, class Layout>
    const Item&
    ArrayDeque<Item, Layout>::operator[](u32 index) const
    {
        return *search(index);
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
} // namespace lgh
