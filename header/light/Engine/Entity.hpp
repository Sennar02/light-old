#ifndef LIGHT_ENGINE_ENTITY_HPP
#define LIGHT_ENGINE_ENTITY_HPP

#include <light/Engine/define.hpp>

namespace lgt
{
    class Entity
    {
    public:
        /**
         *
         */
        Entity();

        /**
         *
         */
        u32
        version() const;

        /**
         *
         */
        u32
        identif() const;

    private:
        friend class EntityManager;

        /**
         *
         */
        Entity(u32 iden, u32 vers);

    protected:
        /**
         *
         */
        u32 m_iden;

        /**
         *
         */
        u32 m_vers;
    };
} // namespace lgt

#endif // LIGHT_ENGINE_ENTITY_HPP
