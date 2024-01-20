#ifndef LIGHT_ENGINE_ENTITY_MANAGER_HPP
#define LIGHT_ENGINE_ENTITY_MANAGER_HPP

#include <light/Engine/define.hpp>
#include <light/Engine/Entity.hpp>

namespace lgt
{
    class EntityManager
    {
    public:
        /**
         *
         */
        EntityManager();

        /**
         *
         */
        Result<Entity, fail::Insert>
        acquire();

        /**
         *
         */
        Result<bool, fail::Remove>
        release(const Entity& entity);

    private:
        /**
         *
         */
        Option<Entity>
        recycle();

    private:
        /**
         *
         */
        ArrayList<Entity> m_list;

        /**
         *
         */
        Entity m_head;

        /**
         *
         */
        u32 m_count;
    };
} // namespace lgt

#endif // LIGHT_ENGINE_ENTITY_MANAGER_HPP
