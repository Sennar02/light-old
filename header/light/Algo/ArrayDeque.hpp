#ifndef LIGHT_ALGO_ARRAY_DEQUE_HPP
#define LIGHT_ALGO_ARRAY_DEQUE_HPP

#include <light/Algo/define.hpp>
#include <light/Algo/ForwIterator.hpp>

namespace lgh
{
    namespace algo
    {
        enum DequeSide
        {
            Head,
            Tail,
        };
    } // namespace algo

    template <class Item, class Layout = FixedLayout>
    class ArrayDeque
    {
    public:
        /**
         *
         */
        ArrayDeque();

        /**
         *
         */
        template <class... Args>
        ArrayDeque(const Array<Item, Layout>& array, Args... args);

        /**
         *
         */
        template <class... Args>
        ArrayDeque(Args... args);

        /**
         *
         */
        virtual ~ArrayDeque() = default;

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
        ArrayDeque&
        for_each(Iter iter, Func func);

        /**
         *
         */
        template <class Iter, class Func>
        const ArrayDeque&
        for_each(Iter iter, Func func) const;

        /**
         *
         */
        template <class Func>
        ArrayDeque&
        for_each(Func func);

        /**
         *
         */
        template <class Func>
        const ArrayDeque&
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
        insert(const Item& item);

        /**
         *
         */
        Result<Item, fail::Remove>
        remove(algo::DequeSide side);

        /**
         *
         */
        ArrayDeque&
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

    private:
        /**
         *
         */
        u32
        next(u32 code, u32 step = 1u) const;

    protected:
        /**
         *
         */
        Array<Item, Layout> m_array;

        /**
         *
         */
        u32 m_delta;

        /**
         *
         */
        u32 m_count;
    };
} // namespace lgh

#include <light/Algo/inline/ArrayDeque.inl>

#endif // LIGHT_ALGO_ARRAY_DEQUE_HPP
