#ifndef LIGHT_ENGINE_ENTITY_FACTORY_HPP
#define LIGHT_ENGINE_ENTITY_FACTORY_HPP

#include <light/Engine/define.hpp>
#include <light/Engine/EntityInfo.hpp>

namespace lgt
{
    template <class Item>
    class EntityFactory
    {
    public:
        /**
         *
         */
        template <class... Args>
        EntityFactory(Args... args);

        /**
         *
         */
        bool
        contains(const Item& item) const;

        /**
         *
         */
        Result<Item, fail::Insert>
        acquire();

        /**
         *
         */
        Result<bool, fail::Remove>
        release(const Item& item);

    private:
        /**
         *
         */
        Option<Item>
        recycle();

    private:
        /**
         *
         */
        ArrayList<Item> m_list;

        /**
         *
         */
        Item m_head;

        /**
         *
         */
        u32 m_count;
    };
} // namespace lgt

#include <light/Engine/inline/EntityFactory.inl>

#endif // LIGHT_ENGINE_ENTITY_FACTORY_HPP
