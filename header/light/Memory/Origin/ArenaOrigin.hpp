#ifndef LIGHT_MEMORY_ORIGIN_ARENA_ORIGIN_HPP
#define LIGHT_MEMORY_ORIGIN_ARENA_ORIGIN_HPP

#include <light/Memory/util.hpp>
#include <light/Memory/Origin/BaseOrigin.hpp>

#include <string.h> // memset

namespace lgt
{
    class ArenaOrigin
        : public BaseOrigin
    {
    public:
        /**
         *
         */
        ArenaOrigin();

        /**
         *
         */
        ArenaOrigin(void* memory, u32 length);

        /**
         *
         */
        virtual u32
        assures(u8 align) const;

        /**
         *
         */
        virtual void
        reset();

        /**
         *
         */
        virtual Result<char*, fail::Acquire>
        acquire(u32 length, u8 align = g_len_u32);

        /**
         *
         */
        virtual Result<bool, fail::Release>
        release(void* memory);

    protected:
        /**
         *
         */
        char* m_border;
    };
} // namespace lgt

#endif // LIGHT_MEMORY_ORIGIN_ARENA_ORIGIN_HPP
