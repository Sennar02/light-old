#include <light/Engine/EntityFactory.hpp>

namespace lgt
{
    template <class Item>
    template <class... Args>
    EntityFactory<Item>::EntityFactory(Args... args)
        : m_list {args...}
        , m_head {0}
        , m_count {0}
    { }

    template <class Item>
    bool
    EntityFactory<Item>::contains(const Item& item) const
    {
        auto info = decode(item);
        auto help = info;

        if ( info.index < m_list.count() )
            help = decode(m_list[info.index]);

        return help.index != info.index;
    }

    template <class Item>
    Result<Item, fail::Insert>
    EntityFactory<Item>::acquire()
    {
        Result<bool, fail::Insert> result;

        auto option = recycle();
        Item item   = 0;

        if ( option.is_fail() ) {
            item   = m_list.count();
            result = m_list.insert(item);

            if ( result.is_fail() )
                return result.fail();
        } else
            item = option.item();

        return item;
    }

    template <class Item>
    Result<bool, fail::Remove>
    EntityFactory<Item>::release(const Item& item)
    {
        auto info = decode(item);

        if ( info.index < m_list.count() ) {
            if ( contains(item) )
                return fail::AlreadyRemoved;

            swap(m_list[info.index], m_head);

            info.epoch += 1u;

            m_head = encode(info);
            m_count += 1u;

        } else
            return fail::UnknownElement;

        return true;
    }

    template <class Item>
    Option<Item>
    EntityFactory<Item>::recycle()
    {
        Option<Item> option = false;

        Item item = m_head;
        auto info = decode(item);

        if ( m_count != 0 ) {
            swap(m_list[info.index], m_head);

            m_count -= 1u;
            option = item;
        }

        return option;
    }
} // namespace lgt
