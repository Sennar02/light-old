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

    Result<char*, fail::Acquire>
    KernOrigin::acquire(u32 length, u8 align)
    {
        if ( is_power_of_two(align) == false )
            return fail::AlignmentFiasco;

        if ( length == 0 ) return fail::NoByteRequested;

        return (char*) calloc(1u, length);
    }

    Result<bool, fail::Release>
    KernOrigin::release(void* memory)
    {
        free(memory);

        return true;
    }
} // namespace lgt
