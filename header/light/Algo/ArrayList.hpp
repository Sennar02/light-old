#ifndef LIGHT_ALGO_ARRAY_LIST_HPP
#define LIGHT_ALGO_ARRAY_LIST_HPP

#include <light/Algo/define.hpp>

namespace lgh
{
    template <class Item, class Layout = FixedLayout>
    class ArrayList
    {
    public:
        /**
         *
         */
        ArrayList();

        /**
         *
         */
        template <class... Args>
        ArrayList(const Array<Item, Layout>& array, Args... args);

        /**
         *
         */
        template <class... Args>
        ArrayList(Args... args);

        /**
         *
         */
        virtual ~ArrayList() = default;

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
        template <class Iter, class Func>
        const ArrayList&
        for_each(Iter& iter, Func func) const;

        /**
         *
         */
        template <class Func>
        const ArrayList&
        for_each(Func func) const;

        /**
         *
         */
        template <class... Args>
        bool
        build(const Array<Item, Layout>& array, Args... args);

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
        insert(const Item& item, u32 index = g_max_u32);

        /**
         *
         */
        Result<Item, fail::Remove>
        remove(u32 index = g_max_u32);

        /**
         *
         */
        ArrayList&
        clear();

        /**
         *
         */
        Item*
        search(u32 index) const;

        /**
         *
         */
        Item&
        find(u32 index, Item& fail) const;

        /**
         *
         */
        const Item&
        find(u32 index, const Item& fail) const;

        /**
         *
         */
        Item&
        operator[](u32 index) const;

        /**
         *
         */
        const Array<Item, Layout>&
        array() const;

    protected:
        /**
         *
         */
        Array<Item, Layout> m_array;

        /**
         *
         */
        u32 m_count;
    };

    template <class Item, class Layout>
    class ArrayListForwIter
    {
    private:
        using List = ArrayList<Item, Layout>;

    public:
        /**
         *
         */
        ArrayListForwIter(const List& list);

        /**
         *
         */
        u32
        index() const;

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
        has_next() const;

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
        const List& m_list;

        /**
         *
         */
        u32 m_index;
    };

    template <class Item, class Layout>
    ArrayListForwIter(const ArrayList<Item, Layout>&)
        -> ArrayListForwIter<Item, Layout>;
} // namespace lgh

#include <light/Algo/inline/ArrayList.inl>

#endif // LIGHT_ALGO_ARRAY_LIST_HPP
