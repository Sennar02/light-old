#include <light/Base/Result.hpp>

namespace lgh
{
    template <class Item, class Fail>
    Result<Item, Fail>::Result()
        : m_valid {false}
    { }

    template <class Item, class Fail>
    Result<Item, Fail>::Result(const Item& item)
        : m_item {item}
        , m_valid {true}
    { }

    template <class Item, class Fail>
    Result<Item, Fail>::Result(const Fail& fail)
        : m_fail {fail}
        , m_valid {false}
    { }

    template <class Item, class Fail>
    bool
    Result<Item, Fail>::is_item() const
    {
        return m_valid;
    }

    template <class Item, class Fail>
    bool
    Result<Item, Fail>::is_item(const Item& item) const
    {
        if ( m_valid && m_item == item )
            return true;

        return false;
    }

    template <class Item, class Fail>
    bool
    Result<Item, Fail>::is_fail() const
    {
        return m_valid == false;
    }

    template <class Item, class Fail>
    bool
    Result<Item, Fail>::is_fail(const Fail& fail) const
    {
        if ( m_valid || m_fail != fail )
            return false;

        return true;
    }

    template <class Item, class Fail>
    const Item&
    Result<Item, Fail>::item(const Item& item) const
    {
        if ( m_valid )
            return m_item;

        return item;
    }

    template <class Item, class Fail>
    Item&
    Result<Item, Fail>::item(Item& item)
    {
        if ( m_valid )
            return m_item;

        return item;
    }

    template <class Item, class Fail>
    Item&
    Result<Item, Fail>::item()
    {
        return m_item;
    }

    template <class Item, class Fail>
    Fail
    Result<Item, Fail>::fail() const
    {
        if ( m_valid )
            return {};

        return m_fail;
    }
} // namespace lgh
