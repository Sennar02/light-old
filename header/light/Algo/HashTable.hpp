#ifndef LIGHT_ALGO_HASH_TABLE_HPP
#define LIGHT_ALGO_HASH_TABLE_HPP

#include <light/Algo/define.hpp>
#include <light/Algo/ForwIterator.hpp>

namespace lgh
{
    struct HashHead
    {
        u32 hash = 0;
        u32 link = 0;
        u32 dist = 1u;
    };

    template <class Name, class Item>
    struct HashBody
    {
        Name name;
        Item item;
        u32  link = 0;
    };

    template <class Name, class Item, class Layout = FixedLayout>
    class HashTable
    {
    public:
        using Head = HashHead;
        using Body = HashBody<Name, Item>;

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
        is_full() const;

        /**
         *
         */
        bool
        is_empty() const;

        /**
         *
         */
        Option<u32>
        index_of(const Name& name) const;

        /**
         *
         */
        bool
        contains(const Name& name) const;

        /**
         *
         */
        template <class Iter, class Func>
        HashTable&
        for_each(Iter iter, Func func);

        /**
         *
         */
        template <class Iter, class Func>
        const HashTable&
        for_each(Iter iter, Func func) const;

        /**
         *
         */
        template <class Func>
        HashTable&
        for_each(Func func);

        /**
         *
         */
        template <class Func>
        const HashTable&
        for_each(Func func) const;

        /**
         *
         */
        template <class... Args>
        bool
        build(const Array<Head, Layout>& heads, const Array<Body, Layout>& array, Args... args);

        /**
         *
         */
        template <class... Args>
        bool
        build(Args... args);

        /**
         *
         */
        bool
        reset();

        /**
         *
         */
        Result<bool, fail::Insert>
        insert(const Name& name, const Item& item);

        /**
         *
         */
        Result<Item, fail::Remove>
        remove(const Name& name);

        /**
         *
         */
        HashTable&
        clear();

        /**
         *
         */
        Item*
        search(const Name& name);

        /**
         *
         */
        const Item*
        search(const Name& name) const;

        /**
         *
         */
        Item&
        find(const Name& name, Item& fail);

        /**
         *
         */
        const Item&
        find(const Name& name, const Item& fail) const;

        /**
         *
         */
        Item&
        operator[](const Name& name);

        /**
         *
         */
        const Item&
        operator[](const Name& name) const;

        /**
         *
         */
        const Array<Head, Layout>&
        heads() const;

        /**
         *
         */
        const Array<Body, Layout>&
        array() const;

    private:
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
} // namespace lgh

#include <light/Algo/inline/HashTable.inl>

#endif // LIGHT_ALGO_HASH_TABLE_HPP
