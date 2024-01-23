#ifndef LIGHT_MEMORY_ORIGIN_BASE_ORIGIN_HPP
#define LIGHT_MEMORY_ORIGIN_BASE_ORIGIN_HPP

#include <light/Memory/define.hpp>

namespace lgh
{
    class BaseOrigin
    {
    public:
        /**
         *
         */
        BaseOrigin();

        /**
         *
         */
        BaseOrigin(void* memory, u32 length);

        /**
         *
         */
        virtual ~BaseOrigin() = default;

        /**
         *
         */
        const char*
        memory() const;

        /**
         *
         */
        u32
        length() const;

        /**
         *
         */
        bool
        contains(void* memory) const;

        /**
         *
         */
        virtual bool
        accepts(void* memory) const;

        /**
         *
         */
        virtual u32
        assures(u8 align) const = 0;

        /**
         *
         */
        virtual void
        reset() = 0;

        /**
         *
         */
        virtual Result<char*, fail::Acquire>
        acquire(u32 length, u8 align = g_len_u32) = 0;

        /**
         *
         */
        virtual Result<bool, fail::Release>
        release(void* memory) = 0;

    protected:
        /**
         *
         */
        char* m_memory;

        /**
         *
         */
        u32 m_length;
    };
} // namespace lgh

#endif // LIGHT_MEMORY_ORIGIN_BASE_ORIGIN_HPP
