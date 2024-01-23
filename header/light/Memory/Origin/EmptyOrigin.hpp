#ifndef LIGHT_MEMORY_ORIGIN_EMPTY_ORIGIN_HPP
#define LIGHT_MEMORY_ORIGIN_EMPTY_ORIGIN_HPP

#include <light/Memory/util.hpp>
#include <light/Memory/Origin/BaseOrigin.hpp>

namespace lgh
{
    class EmptyOrigin
        : public BaseOrigin
    {
    public:
        /**
         *
         */
        EmptyOrigin();

        /**
         *
         */
        EmptyOrigin(void* memory, u32 length);

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
    };
} // namespace lgh

#endif // LIGHT_MEMORY_ORIGIN_EMPTY_ORIGIN_HPP
