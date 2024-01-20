#include <light/Memory/Origin/PoolOrigin.hpp>

namespace lgt
{
    union Head
    {
        struct Info
        {
            bool used;
        } info;

        char pref[8u];
    };

    static const u32 g_len_head =
        sizeof(Head);

    static const u32 g_len_node =
        g_len_upt;

    PoolOrigin::PoolOrigin()
        : BaseOrigin()
        , m_list {0}
        , m_count {0}
        , m_page {g_len_node}
    { }

    PoolOrigin::PoolOrigin(void* memory, u32 length, u32 page)
        : BaseOrigin(memory, length)
        , m_list {0}
        , m_count {0}
        , m_page {g_len_node}
    {
        reset(page);
    }

    u32
    PoolOrigin::count() const
    {
        return m_count;
    }

    u32
    PoolOrigin::page() const
    {
        return m_page - g_len_head;
    }

    bool
    PoolOrigin::accepts(void* memory) const
    {
        u32 diff = (char*) memory - m_memory;
        u32 dist = diff - g_len_head;

        if ( contains(memory) )
            return dist % m_page == 0;

        return false;
    }

    u32
    PoolOrigin::assures(u8 align) const
    {
        if ( align == g_len_u8 ) {
            if ( m_count != 0 )
                return m_page - g_len_head;
        }

        return 0;
    }

    void
    PoolOrigin::reset(u32 page)
    {
        char* addr  = m_memory;
        u32   count = 0;

        if ( page >= g_len_node ) {
            if ( m_memory != 0 ) {
                memset(m_memory, 0, m_length);

                m_page = page + g_len_head;
                count  = m_length / m_page;

                for ( u32 i = 0; i < count; i++ )
                    insert(addr + m_page * i);
            }
        }
    }

    void
    PoolOrigin::reset()
    {
        reset(m_page - g_len_head);
    }

    Result<char*, fail::Acquire>
    PoolOrigin::acquire(u32 length, u8 align)
    {
        char* addr = (char*) remove(length);
        Head* head = (Head*) (addr - g_len_head);

        if ( align != g_len_u8 )
            return fail::AlignmentFiasco;

        if ( length == 0 ) return fail::NoByteRequested;

        if ( addr != 0 ) {
            head->info.used = true;

            return (char*)
                memset(addr, 0, page());
        }

        return fail::NotEnoughMemory;
    }

    Result<char*, fail::Acquire>
    PoolOrigin::acquire()
    {
        return acquire(m_page - g_len_head);
    }

    Result<bool, fail::Release>
    PoolOrigin::release(void* memory)
    {
        char* addr = (char*) memory;
        Head* head = (Head*) (addr - g_len_head);

        if ( memory != 0 ) {
            if ( accepts(memory) == false )
                return fail::NotMemoryParent;

            if ( head->info.used ) {
                head->info.used = false;

                insert(addr);
            } else
                return fail::AlreadyReleased;
        }

        return true;
    }

    void*
    PoolOrigin::remove(u32 length)
    {
        void** node = m_list;
        u32    page = m_page - g_len_head;

        if ( length == 0 ) return 0;

        if ( length <= page && m_count != 0 ) {
            m_list = (void**) *node;
            m_count -= 1u;

            return (char*) node;
        }

        return 0;
    }

    void
    PoolOrigin::insert(void* memory)
    {
        char*  addr = (char*) memory + g_len_head;
        void** node = (void**) addr;

        if ( memory != 0 ) {
            *node  = (void*) m_list;
            m_list = node;

            m_count += 1u;
        }
    }
} // namespace lgt
