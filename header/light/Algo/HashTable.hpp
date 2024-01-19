#ifndef LIGHT_ALGO_HASH_TABLE_HPP
#define LIGHT_ALGO_HASH_TABLE_HPP

#include <light/Algo/define.hpp>

namespace lgt
{
    template <class Name>
    struct HashHead
    {
        LGT_UNDEF(Name, name);

        u32 hash = 0;
        u32 dist = 1u;
    };

    template <class Item>
    struct HashBody
    {
        LGT_UNDEF(Item, item);
    };

    template <class Name, class Item, class Layout = FixedLayout>
    class HashTable
    {
    public:
        using Head = HashHead<Name>;
        using Body = HashBody<Item>;

    public:
        /**
         *
         */
        HashTable();

        /**
         *
         */
        template <class... Args>
        HashTable(const Array<Head, Layout>& heads, const Array<Body, Layout>& array, Args... args);

        /**
         *
         */
        template <class... Args>
        HashTable(Args... args);

        /**
         *
         */
        virtual ~HashTable() = default;

        /**
         *
         */
        u32
        size() const;

        /**
         *
         */
        u32
        count() const;

        /**
         *
         */
        bool
        is_empty() const;

        /**
         *
         */
        bool
        is_full() const;

        /**
         *
         */
        bool
        contains(const Name& name) const;

        /**
         *
         */
        Result<bool, err::Insert>
        insert(const Name& name, const Item& item);

        /**
         *
         */
        Result<Item, err::Remove>
        remove(const Name& name);

        /**
         *
         */
        template <class Func>
        HashTable&
        for_each(Func func);

        /**
         *
         */
        HashTable&
        clear();

        /**
         *
         */
        Option<Item&>
        find(const Name& name) const;

        /**
         *
         */
        Item&
        operator[](const Name& name) const;

        /**
         *
         */
        const Array<Head>&
        heads() const;

        /**
         *
         */
        const Array<Body>&
        array() const;

    private:
        /**
         *
         */
        u32
        index_of(const Name& name) const;

        /**
         *
         */
        u32
        code(const Name& name) const;

        /**
         *
         */
        u32
        next(u32 code, u32 step = 1u) const;

    protected:
        /**
         *
         */
        Array<Head, Layout> m_heads;

        /**
         *
         */
        Array<Body, Layout> m_array;

        /**
         *
         */
        u32 m_count;
    };

    template <class Name, class Item, class Layout>
    class HashTableForwIter
    {
    private:
        using Table = HashTable<Name, Item, Layout>;

    public:
        /**
         *
         */
        HashTableForwIter(const Table& table);

        /**
         *
         */
        const Name&
        name() const;

        /**
         *
         */
        Item&
        item();

        /**
         *
         */
        const Item&
        item() const;

        /**
         *
         */
        bool
        hasNext() const;

        /**
         *
         */
        bool
        next();

        /**
         *
         */
        void
        reset();

    private:
        /**
         *
         */
        const Table& m_table;

        /**
         *
         */
        u32 m_index;
    };

    template <class Name, class Item, class Layout>
    HashTable(const Layout&, const Layout&)
        -> HashTable<Name, Item, Layout>;

    template <class Name, class Item, class Layout>
    HashTableForwIter(const HashTable<Name, Item, Layout>&)
        -> HashTableForwIter<Name, Item, Layout>;
} // namespace lgt

#include <light/Algo/inline/HashTable.inl>

#endif // LIGHT_ALGO_HASH_TABLE_HPP
