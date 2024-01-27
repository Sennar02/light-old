#include <light/Memory/util.hpp>

namespace lgh
{
    template <class Origin>
    char*
    acquire(Origin& origin, u32 length, u8 align)
    {
        auto result = origin.acquire(length, align);

        if ( result.is_item() )
            return result.item();

        // clang-format off
        fprintf(stderr, "[\x1b[31mFAIL\x1b[0m] %s\n",
            fail::g_acquire[result.fail()]);
        // clang-format on

        exit(EXIT_FAILURE);
    }
} // namespace lgh
