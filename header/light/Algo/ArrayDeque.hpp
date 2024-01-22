#ifndef LIGHT_ALGO_ARRAY_DEQUE_HPP
#define LIGHT_ALGO_ARRAY_DEQUE_HPP

#include <light/Algo/define.hpp>

namespace lgt
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
        for_each(Iter& iter, Func func);

        /**
         *
         */
        template <class Func>
        ArrayDeque&
        for_each(Func func);

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
        Item&
        find(u32 index) const;

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

    template <class Item, class Layout>
    class ArrayDequeForwIter
    {
    private:
        using Deque = ArrayDeque<Item, Layout>;

    public:
        /**
         *
         */
        ArrayDequeForwIter(const Deque& deque);

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
        const Deque& m_deque;

        /**
         *
         */
        u32 m_index;
    };

    template <class Item, class Layout>
    ArrayDequeForwIter(const ArrayList<Item, Layout>&)
        -> ArrayDequeForwIter<Item, Layout>;
} // namespace lgt

#include <light/Algo/inline/ArrayDeque.inl>

#endif // LIGHT_ALGO_ARRAY_DEQUE_HPP
