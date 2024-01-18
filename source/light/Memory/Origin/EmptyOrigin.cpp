#include <light/Memory/Origin/EmptyOrigin.hpp>

namespace lgt
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

    Result<char*, err::Acquire>
    EmptyOrigin::acquire(u32 length, u8 align)
    {
        if ( is_power_of_two(align) == false )
            return err::AlignmentFiasco;

        if ( length == 0 ) return err::NoByteRequested;

        return 0;
    }

    Result<bool, err::Release>
    EmptyOrigin::release(void* memory)
    {
        if ( memory == 0 )
            return true;

        return err::NotMemoryParent;
    }
} // namespace lgt
