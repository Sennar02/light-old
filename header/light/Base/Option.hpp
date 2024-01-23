#ifndef LIGHT_BASE_OPTION_HPP
#define LIGHT_BASE_OPTION_HPP

namespace lgh
{
    template <class Item>
    class Option
    {
    public:
        /**
         *
         */
        Option();

        /**
         *
         */
        Option(const Item& item);

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

    private:
        union
        {
            /**
             *
             */
            Item m_item;
        };

        /**
         *
         */
        bool m_valid;
    };
} // namespace lgh

#include <light/Base/inline/Option.inl>

#endif // LIGHT_BASE_OPTION_HPP
