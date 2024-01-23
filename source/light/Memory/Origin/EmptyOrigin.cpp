#include <light/Memory/Origin/EmptyOrigin.hpp>

namespace lgh
{
    EmptyOrigin::EmptyOrigin()
        : BaseOrigin()
    { }

    EmptyOrigin::EmptyOrigin(void*, u32)
        : BaseOrigin()
    { }

    u32
    EmptyOrigin::assures(u8) const
    {
        return 0;
    }

    void
    EmptyOrigin::reset()
    { }

    Result<char*, fail::Acquire>
    EmptyOrigin::acquire(u32 length, u8 align)
    {
        if ( is_power_of_two(align) == false )
            return fail::AlignmentFiasco;

        if ( length == 0 ) return fail::NoByteRequested;

        return 0;
    }

    Result<bool, fail::Release>
    EmptyOrigin::release(void* memory)
    {
        if ( memory == 0 )
            return true;

        return fail::NotMemoryParent;
    }
} // namespace lgh
