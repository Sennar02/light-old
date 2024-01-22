#ifndef LIGHT_BASE_RESULT_HPP
#define LIGHT_BASE_RESULT_HPP

namespace lgt
{
    template <class Item, class Fail>
    class Result
    {
    public:
        /**
         *
         */
        Result();

        /**
         *
         */
        Result(const Item& item);

        /**
         *
         */
        Result(const Fail& fail);

        /**
         *
         */
        bool
        is_item() const;

        /**
         *
         */
        bool
        is_item(const Item& item) const;

        /**
         *
         */
        bool
        is_fail() const;

        /**
         *
         */
        bool
        is_fail(const Fail& fail) const;

        /**
         *
         */
        const Item&
        item(const Item& item) const;

        /**
         *
         */
        Item&
        item(Item& item);

        /**
         *
         */
        Item&
        item();

        /**
         *
         */
        Fail
        fail() const;

    private:
        /**
         *
         */
        LGT_UNDEF(Item, m_item);

        /**
         *
         */
        LGT_UNDEF(Fail, m_fail);

        /**
         *
         */
        bool m_valid;
    };
} // namespace lgt

#include <light/Base/inline/Result.inl>

#endif // LIGHT_BASE_RESULT_HPP
