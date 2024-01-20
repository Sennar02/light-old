#include <light/Engine/Entity.hpp>

namespace lgt
{
    Entity::Entity()
        : Entity(g_max_u32, g_max_u32)
    { }

    Entity::Entity(u32 iden, u32 vers)
        : m_iden {iden}
        , m_vers {vers}
    { }

    u32
    Entity::version() const
    {
        return m_vers;
    }

    u32
    Entity::identif() const
    {
        return m_iden;
    }
} // namespace lgt
