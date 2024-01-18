#ifndef LIGHT_MEMORY_ORIGIN_POOL_ORIGIN_HPP
#define LIGHT_MEMORY_ORIGIN_POOL_ORIGIN_HPP

#include <light/Memory/util.hpp>
#include <light/Memory/Origin/BaseOrigin.hpp>

namespace lgt
{
    class PoolOrigin
        : public BaseOrigin
    {
    public:
        /**
         *
         */
        PoolOrigin();

        /**
         *
         */
        PoolOrigin(void* memory, u32 length, u32 page);

        /**
         *
         */
        u32
        count() const;

        /**
         *
         */
        u32
        page() const;

        /**
         *
         */
        virtual bool
        accepts(void* memory) const;

        /**
         *
         */
        virtual u32
        assures(u8 align) const;

        /**
         *
         */
        virtual void
        reset(u32 page);

        /**
         *
         */
        virtual void
        reset();

        /**
         *
         */
        virtual Result<char*, err::Acquire>
        acquire(u32 length, u8 align = g_len_u8);

        /**
         *
         */
        virtual Result<char*, err::Acquire>
        acquire();

        /**
         *
         */
        virtual Result<bool, err::Release>
        release(void* memory);

    private:
        /**
         *
         */
        void*
        remove(u32 length);

        /**
         *
         */
        void
        insert(void* memory);

    protected:
        /**
         *
         */
        void** m_list;

        /**
         *
         */
        u32 m_count;

        /**
         *
         */
        u32 m_page;
    };
} // namespace lgt

#endif // LIGHT_MEMORY_ORIGIN_POOL_ORIGIN_HPP
