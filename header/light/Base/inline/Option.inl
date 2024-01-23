#include <light/Base/Option.hpp>

namespace lgh
{
    template <class Item>
    Option<Item>::Option()
        : m_valid {false}
    { }

    template <class Item>
    Option<Item>::Option(const Item& item)
        : m_item {item}
        , m_valid {true}
    { }

    template <class Item>
    bool
    Option<Item>::is_item() const
    {
        return m_valid;
    }

    template <class Item>
    bool
    Option<Item>::is_item(const Item& item) const
    {
        if ( m_valid && m_item == item )
            return true;

        return false;
    }

    template <class Item>
    bool
    Option<Item>::is_fail() const
    {
        return m_valid == false;
    }

    template <class Item>
    const Item&
    Option<Item>::item(const Item& item) const
    {
        if ( m_valid )
            return m_item;

        return item;
    }

    template <class Item>
    Item&
    Option<Item>::item(Item& item)
    {
        if ( m_valid )
            return m_item;

        return item;
    }

    template <class Item>
    Item&
    Option<Item>::item()
    {
        return m_item;
    }
} // namespace lgh
