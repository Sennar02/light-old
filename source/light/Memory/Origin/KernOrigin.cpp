#include <light/Memory/Origin/KernOrigin.hpp>

namespace lgt
{
    KernOrigin::KernOrigin()
        : BaseOrigin()
    { }

    KernOrigin::KernOrigin(void*, u32)
        : BaseOrigin()
    { }

    u32
    KernOrigin::assures(u8 align) const
    {
        if ( is_power_of_two(align) == false )
            return 0;

        return g_max_u32;
    }

    void
    KernOrigin::reset()
    { }

    Result<char*, err::Acquire>
    KernOrigin::acquire(u32 length, u8 align)
    {
        if ( is_power_of_two(align) == false )
            return err::AlignmentFiasco;

        if ( length == 0 ) return err::NoByteRequested;

        return (char*) calloc(1u, length);
    }

    Result<bool, err::Release>
    KernOrigin::release(void* memory)
    {
        free(memory);

        return true;
    }
} // namespace lgt
