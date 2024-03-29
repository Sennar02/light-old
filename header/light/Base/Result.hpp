#ifndef LIGHT_BASE_RESULT_HPP
#define LIGHT_BASE_RESULT_HPP

namespace lgh
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
        union
        {
            /**
             *
             */
            Item m_item;

            /**
             *
             */
            Fail m_fail;
        };

        /**
         *
         */
        bool m_valid;
    };
} // namespace lgh

#include <light/Base/inline/Result.inl>

#endif // LIGHT_BASE_RESULT_HPP
