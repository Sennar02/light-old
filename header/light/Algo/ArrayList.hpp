#ifndef LIGHT_ALGO_ARRAY_LIST_HPP
#define LIGHT_ALGO_ARRAY_LIST_HPP

#include <light/Algo/define.hpp>
#include <light/Algo/ForwIterator.hpp>

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
        ArrayList&
        for_each(Iter iter, Func func);

        /**
         *
         */
        template <class Iter, class Func>
        const ArrayList&
        for_each(Iter iter, Func func) const;

        /**
         *
         */
        template <class Func>
        ArrayList&
        for_each(Func func);

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
        search(u32 index);

        /**
         *
         */
        const Item*
        search(u32 index) const;

        /**
         *
         */
        Item&
        find(u32 index, Item& fail);

        /**
         *
         */
        const Item&
        find(u32 index, const Item& fail) const;

        /**
         *
         */
        Item&
        operator[](u32 index);

        /**
         *
         */
        const Item&
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
} // namespace lgh

#include <light/Algo/inline/ArrayList.inl>

#endif // LIGHT_ALGO_ARRAY_LIST_HPP
