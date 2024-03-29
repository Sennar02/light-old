#include <light/Algo/HashTable.hpp>

namespace lgh
{
    template <class Name, class Item, class Layout>
    HashTable<Name, Item, Layout>::HashTable()
        : m_heads {}
        , m_array {}
        , m_count {0}
    { }

    template <class Name, class Item, class Layout>
    template <class... Args>
    HashTable<Name, Item, Layout>::HashTable(const Array<Head, Layout>& heads, const Array<Body, Layout>& array, Args... args)
        : m_heads {heads, args...}
        , m_array {array, args...}
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
        u32 size =
            min(m_heads.length(), m_array.length());

        return size;
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
        u32 size =
            min(m_heads.length(), m_array.length());

        return m_count == size;
    }

    template <class Name, class Item, class Layout>
    bool
    HashTable<Name, Item, Layout>::is_empty() const
    {
        return m_count == 0;
    }

    template <class Name, class Item, class Layout>
    Option<u32>
    HashTable<Name, Item, Layout>::index_of(const Name& name) const
    {
        u32         hash = code(name);
        const Head* iter = 0;
        const Body* pair = 0;

        if ( is_empty() ) return {};

        for ( u32 i = hash; hash != next(i); i = next(i) ) {
            iter = &m_heads[i];
            pair = &m_array[iter->link];

            if ( iter->dist == 0 ) break;

            if ( iter->hash == hash ) {
                if ( Equals<Name>::equals(pair->name, name) )
                    return i;
            }
        }

        return {};
    }

    template <class Name, class Item, class Layout>
    bool
    HashTable<Name, Item, Layout>::contains(const Name& name) const
    {
        auto option = index_of(name);
        u32  index  = option.item();

        if ( option.is_item() ) {
            if ( index < m_heads.length() )
                return true;
        }

        return false;
    }

    template <class Name, class Item, class Layout>
    template <class Iter, class Func>
    HashTable<Name, Item, Layout>&
    HashTable<Name, Item, Layout>::for_each(Iter iter, Func func)
    {
        u32         index = 0;
        const Name* name  = 0;
        Item*       item  = 0;

        if ( is_empty() ) return *this;

        while ( iter.has_next(m_count) ) {
            index = iter.next(m_count);
            name  = &m_array[index].name;
            item  = &m_array[index].item;

            func(*item, *name);
        }

        return *this;
    }

    template <class Name, class Item, class Layout>
    template <class Iter, class Func>
    const HashTable<Name, Item, Layout>&
    HashTable<Name, Item, Layout>::for_each(Iter iter, Func func) const
    {
        u32         index = 0;
        const Name* name  = 0;
        const Item* item  = 0;

        if ( is_empty() ) return *this;

        while ( iter.has_next(m_count) ) {
            index = iter.next(m_count);
            name  = &m_array[index].name;
            item  = &m_array[index].item;

            func(*item, *name);
        }

        return *this;
    }

    template <class Name, class Item, class Layout>
    template <class Func>
    HashTable<Name, Item, Layout>&
    HashTable<Name, Item, Layout>::for_each(Func func)
    {
        return for_each(ForwIterator {}, func);
    }

    template <class Name, class Item, class Layout>
    template <class Func>
    const HashTable<Name, Item, Layout>&
    HashTable<Name, Item, Layout>::for_each(Func func) const
    {
        return for_each(ForwIterator {}, func);
    }

    template <class Name, class Item, class Layout>
    template <class... Args>
    bool
    HashTable<Name, Item, Layout>::build(const Array<Head, Layout>& heads, const Array<Body, Layout>& array, Args... args)
    {
        if ( reset() == false )
            return false;

        ctor(m_heads, heads, args...);
        ctor(m_array, array, args...);

        return true;
    }

    template <class Name, class Item, class Layout>
    template <class... Args>
    bool
    HashTable<Name, Item, Layout>::build(Args... args)
    {
        if ( reset() == false )
            return false;

        ctor(m_heads, args...);
        ctor(m_array, args...);

        return true;
    }

    template <class Name, class Item, class Layout>
    bool
    HashTable<Name, Item, Layout>::reset()
    {
        bool result = m_heads.resize(0) &&
                      m_array.resize(0);

        if ( result )
            m_count = 0;

        return result;
    }

    template <class Name, class Item, class Layout>
    Result<bool, fail::Insert>
    HashTable<Name, Item, Layout>::insert(const Name& name, const Item& item)
    {
        u32   hash = code(name);
        Head* iter = 0;
        Body* pair = 0;
        Head  head = {hash, m_count};
        Body  body = {name, item};

        if ( is_full() ) return fail::NotEnoughSpace;

        for ( u32 i = hash; true; i = next(i) ) {
            iter = &m_heads[i];
            pair = &m_array[iter->link];

            m_array[head.link].link = i;

            if ( iter->dist != 0 && iter->hash == hash ) {
                if ( Equals<Name>::equals(pair->name, name) )
                    return fail::NameRepetition;
            }

            if ( iter->dist < head.dist ) {
                if ( iter->dist == 0 ) {
                    body.link = m_array[m_count].link;

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
    HashTable<Name, Item, Layout>::remove(const Name& name)
    {
        auto option = index_of(name);
        u32  index  = option.item();

        if ( option.is_item() ) {
            if ( index < m_heads.length() ) {
                // scambiare:  array[heads[index].link] <-> array[count]
                // eliminare:  heads[index] <- 0
                // correggere: heads[array[count].link].link <- index
            }
        }

        return fail::UnknownElement;
    }

    template <class Name, class Item, class Layout>
    HashTable<Name, Item, Layout>&
    HashTable<Name, Item, Layout>::clear()
    {
        m_count = 0;

        return *this;
    }

    template <class Name, class Item, class Layout>
    Item*
    HashTable<Name, Item, Layout>::search(const Name& name)
    {
        auto option = index_of(name);
        u32  index  = option.item();

        if ( option.is_item() ) {
            if ( index < m_heads.length() )
                return &m_array[m_heads[index].link].item;
        }

        return 0;
    }

    template <class Name, class Item, class Layout>
    const Item*
    HashTable<Name, Item, Layout>::search(const Name& name) const
    {
        auto option = index_of(name);
        u32  index  = option.item();

        if ( option.is_item() ) {
            if ( index < m_heads.length() )
                return &m_array[m_heads[index].link].item;
        }

        return 0;
    }

    template <class Name, class Item, class Layout>
    Item&
    HashTable<Name, Item, Layout>::find(const Name& name, Item& fail)
    {
        auto option = index_of(name);
        u32  index  = option.item();

        if ( option.is_item() ) {
            if ( index < m_heads.length() )
                return m_array[m_heads[index].link].item;
        }

        return fail;
    }

    template <class Name, class Item, class Layout>
    const Item&
    HashTable<Name, Item, Layout>::find(const Name& name, const Item& fail) const
    {
        auto option = index_of(name);
        u32  index  = option.item();

        if ( option.is_item() ) {
            if ( index < m_heads.length() )
                return m_array[m_heads[index].link].item;
        }

        return fail;
    }

    template <class Name, class Item, class Layout>
    Item&
    HashTable<Name, Item, Layout>::operator[](const Name& name)
    {
        return *search(name);
    }

    template <class Name, class Item, class Layout>
    const Item&
    HashTable<Name, Item, Layout>::operator[](const Name& name) const
    {
        return *search(name);
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
        u32 length = m_heads.length();

        if ( length != 0 )
            return (code + step) % length;

        return length;
    }

} // namespace lgh
