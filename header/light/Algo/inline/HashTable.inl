#include <light/Algo/HashTable.hpp>

namespace lgt
{
    template <class Name, class Item, class Layout>
    HashTable<Name, Item, Layout>::HashTable()
        : m_heads {}
        , m_array {}
        , m_count {0}
    { }

    template <class Name, class Item, class Layout>
    template <class... Args>
    HashTable<Name, Item, Layout>::HashTable(Args... args)
        : m_heads {args...}
        , m_array {args...}
        , m_count {0}
    { }

    template <class Name, class Item, class Layout>
    u32
    HashTable<Name, Item, Layout>::size() const
    {
        return m_heads.length();
    }

    template <class Name, class Item, class Layout>
    u32
    HashTable<Name, Item, Layout>::count() const
    {
        return m_count;
    }

    template <class Name, class Item, class Layout>
    bool
    HashTable<Name, Item, Layout>::is_full() const
    {
        return m_count == m_heads.length();
    }

    template <class Name, class Item, class Layout>
    bool
    HashTable<Name, Item, Layout>::is_empty() const
    {
        return m_count == 0;
    }

    template <class Name, class Item, class Layout>
    u32
    HashTable<Name, Item, Layout>::index_of(const Name& name) const
    {
        u32   hash = code(name);
        Head* iter = 0;
        Body* pair = 0;

        if ( is_empty() ) return g_max_u32;

        for ( u32 i = hash; hash != next(i); i = next(i) ) {
            iter = &m_heads[i];
            pair = &m_array[iter->link];

            if ( iter->dist != 0 && iter->hash == hash ) {
                if ( Compare<Name>::equals(pair->name, name) )
                    return i;
            }
        }

        return g_max_u32;
    }

    template <class Name, class Item, class Layout>
    bool
    HashTable<Name, Item, Layout>::contains(const Name& name) const
    {
        u32 index = index_of(name);

        if ( index < m_heads.length() )
            return true;

        return false;
    }

    template <class Name, class Item, class Layout>
    Result<bool, fail::Insert>
    HashTable<Name, Item, Layout>::insert(const Name& name, const Item& item)
    {
        u32   hash = code(name);
        Head* iter = 0;
        Body* pair = 0;
        Head  head = {hash, m_count};
        Body  body = {name, item, hash};

        if ( is_full() ) return fail::NotEnoughSpace;

        for ( u32 i = hash; true; i = next(i) ) {
            iter = &m_heads[i];
            pair = &m_array[iter->link];

            m_array[head.link].link = i;

            if ( iter->dist != 0 && iter->hash == hash ) {
                if ( Compare<Name>::equals(pair->name, name) )
                    return fail::NameRepetition;
            }

            if ( iter->dist < head.dist ) {
                if ( iter->dist == 0 ) {
                    if ( head.link == m_count ) body.link = i;

                    ctor(m_heads[i], head);
                    ctor(m_array[m_count], body);

                    m_count += 1u;

                    return true;
                }

                swap(m_heads[i], head);
                swap(m_array[head.link].link, body.link);
            }

            head.dist += 1u;
        }
    }

    template <class Name, class Item, class Layout>
    Result<Item, fail::Remove>
    HashTable<Name, Item, Layout>::remove(const Name&)
    {
        // u32 index = index_of(name);

        // if ( index < m_array.length() )
        //     m_array[index].dist = 0;
        // else
        //     return fail::UnknownElement;

        // return m_array[index].item;

        return fail::UnknownElement;
    }

    template <class Name, class Item, class Layout>
    template <class Iter, class Func>
    HashTable<Name, Item, Layout>&
    HashTable<Name, Item, Layout>::for_each(Iter& iter, Func func)
    {
        while ( iter.next() )
            func(iter.item(), iter.name());

        return *this;
    }

    template <class Name, class Item, class Layout>
    template <class Func>
    HashTable<Name, Item, Layout>&
    HashTable<Name, Item, Layout>::for_each(Func func)
    {
        HashTableForwIter iter = {*this};

        while ( iter.next() )
            func(iter.item(), iter.name());

        return *this;
    }

    template <class Name, class Item, class Layout>
    HashTable<Name, Item, Layout>&
    HashTable<Name, Item, Layout>::clear()
    {
        m_count = 0;

        return *this;
    }

    template <class Name, class Item, class Layout>
    Option<Item&>
    HashTable<Name, Item, Layout>::find(const Name& name) const
    {
        u32 index = index_of(name);

        if ( index < m_heads.length() )
            return m_array[m_heads[index].link].item;

        return true;
    }

    template <class Name, class Item, class Layout>
    Option<Item&>
    HashTable<Name, Item, Layout>::operator[](const Name& name) const
    {
        return find(name);
    }

    template <class Name, class Item, class Layout>
    const Array<HashHead, Layout>&
    HashTable<Name, Item, Layout>::heads() const
    {
        return m_heads;
    }

    template <class Name, class Item, class Layout>
    const Array<HashBody<Name, Item>, Layout>&
    HashTable<Name, Item, Layout>::array() const
    {
        return m_array;
    }

    template <class Name, class Item, class Layout>
    u32
    HashTable<Name, Item, Layout>::code(const Name& name) const
    {
        return next(Hash<Name>::code(name), 0);
    }

    template <class Name, class Item, class Layout>
    u32
    HashTable<Name, Item, Layout>::next(u32 code, u32 step) const
    {
        u32 length = m_array.length();

        if ( length != 0 )
            return (code + step) % length;

        return length;
    }

    template <class Name, class Item, class Layout>
    HashTableForwIter<Name, Item, Layout>::HashTableForwIter(const Table& table)
        : m_table {table}
        , m_index {g_max_u32}
    { }

    template <class Name, class Item, class Layout>
    const Name&
    HashTableForwIter<Name, Item, Layout>::name() const
    {
        return m_table.array()[m_index].name;
    }

    template <class Name, class Item, class Layout>
    Item&
    HashTableForwIter<Name, Item, Layout>::item()
    {
        return m_table.array()[m_index].item;
    }

    template <class Name, class Item, class Layout>
    const Item&
    HashTableForwIter<Name, Item, Layout>::item() const
    {
        return m_table.array()[m_index].item;
    }

    template <class Name, class Item, class Layout>
    bool
    HashTableForwIter<Name, Item, Layout>::has_next() const
    {
        u32 next = m_index + 1u;

        if ( next < m_table.count() )
            return true;

        return false;
    }

    template <class Name, class Item, class Layout>
    bool
    HashTableForwIter<Name, Item, Layout>::next()
    {
        u32 next = m_index + 1u;

        if ( next < m_table.count() )
            m_index = next;

        return m_index == next;
    }

    template <class Name, class Item, class Layout>
    void
    HashTableForwIter<Name, Item, Layout>::reset()
    {
        m_index = g_max_u32;
    }
} // namespace lgt
