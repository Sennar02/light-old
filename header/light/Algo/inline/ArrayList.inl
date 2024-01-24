#include <light/Algo/ArrayList.hpp>

namespace lgh
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
    template <class Iter, class Func>
    ArrayList<Item, Layout>&
    ArrayList<Item, Layout>::for_each(Iter iter, Func func)
    {
        u32   index = 0;
        Item* item  = 0;

        if ( is_empty() ) return *this;

        while ( iter.has_next(m_count) ) {
            index = iter.next(m_count);
            item  = &m_array[index];

            func(*item, index);
        }

        return *this;
    }

    template <class Item, class Layout>
    template <class Iter, class Func>
    const ArrayList<Item, Layout>&
    ArrayList<Item, Layout>::for_each(Iter iter, Func func) const
    {
        u32         index = 0;
        const Item* item  = 0;

        if ( is_empty() ) return *this;

        while ( iter.has_next(m_count) ) {
            index = iter.next(m_count);
            item  = &m_array[index];

            func(*item, index);
        }

        return *this;
    }

    template <class Item, class Layout>
    template <class Func>
    ArrayList<Item, Layout>&
    ArrayList<Item, Layout>::for_each(Func func)
    {
        return for_each(ForwIterator {}, func);
    }

    template <class Item, class Layout>
    template <class Func>
    const ArrayList<Item, Layout>&
    ArrayList<Item, Layout>::for_each(Func func) const
    {
        return for_each(ForwIterator {}, func);
    }

    template <class Item, class Layout>
    template <class... Args>
    bool
    ArrayList<Item, Layout>::build(const Array<Item, Layout>& array, Args... args)
    {
        if ( reset() == false )
            return false;

        ctor(m_array, array, args...);

        return true;
    }

    template <class Item, class Layout>
    template <class... Args>
    bool
    ArrayList<Item, Layout>::build(Args... args)
    {
        if ( reset() == false )
            return false;

        ctor(m_array, args...);

        return true;
    }

    template <class Item, class Layout>
    bool
    ArrayList<Item, Layout>::reset()
    {
        bool result = m_array.resize(0);

        if ( result )
            m_count = 0;

        return result;
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
    ArrayList<Item, Layout>&
    ArrayList<Item, Layout>::clear()
    {
        m_count = 0;

        return *this;
    }

    template <class Item, class Layout>
    Item*
    ArrayList<Item, Layout>::search(u32 index)
    {
        if ( index < m_array.length() )
            return &m_array[index];

        return 0;
    }

    template <class Item, class Layout>
    const Item*
    ArrayList<Item, Layout>::search(u32 index) const
    {
        if ( index < m_array.length() )
            return &m_array[index];

        return 0;
    }

    template <class Item, class Layout>
    Item&
    ArrayList<Item, Layout>::find(u32 index, Item& fail)
    {
        if ( index < m_array.length() )
            return m_array[index];

        return fail;
    }

    template <class Item, class Layout>
    const Item&
    ArrayList<Item, Layout>::find(u32 index, const Item& fail) const
    {
        if ( index < m_array.length() )
            return m_array[index];

        return fail;
    }

    template <class Item, class Layout>
    Item&
    ArrayList<Item, Layout>::operator[](u32 index)
    {
        return *search(index);
    }

    template <class Item, class Layout>
    const Item&
    ArrayList<Item, Layout>::operator[](u32 index) const
    {
        return *search(index);
    }

    template <class Item, class Layout>
    const Array<Item, Layout>&
    ArrayList<Item, Layout>::array() const
    {
        return m_array;
    }
} // namespace lgh
