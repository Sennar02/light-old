#include <light/Engine/EntityManager.hpp>

namespace lgt
{
    static Entity g_buffer[g_KiB] = {};

    EntityManager::EntityManager()
        : m_list {g_buffer, g_KiB}
        , m_head {}
        , m_count {0}
    { }

    Result<Entity, fail::Insert>
    EntityManager::acquire()
    {
        using Return = Result<bool, fail::Insert>;

        auto   option = recycle();
        Return result = fail::NotEnoughSpace;
        Entity entity;

        if ( option.is_fail() ) {
            entity = {m_list.count(), 0};
            result = m_list.insert(entity);

            if ( result.is_fail() )
                return result.fail();
        } else
            entity = option.succ(entity);

        return entity;
    }

    Result<bool, fail::Remove>
    EntityManager::release(const Entity& entity)
    {
        u32 iden = entity.m_iden;

        if ( iden >= m_list.count() )
            return fail::UnknownElement;

        if ( m_list[iden].m_iden == iden ) {
            swap(m_list[iden], m_head);

            m_head.m_vers += 1u;
            m_count += 1u;
        } else
            return fail::AlreadyRemoved;

        return true;
    }

    Option<Entity>
    EntityManager::recycle()
    {
        Entity entity = m_head;
        u32    iden   = m_head.m_iden;

        if ( m_count != 0 ) {
            m_count -= 1u;
            swap(m_list[iden], m_head);

            return entity;
        }

        return true;
    }
} // namespace lgt
