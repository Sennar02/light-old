#include <light/Engine/import.hpp>
#include <stdio.h>

using namespace lgt;

int
main(int, const char*[])
{
    EntityFactory<u32> factory = {g_origin, 256u};

    u32 count = EntityTraits<u32>::s_whole_bits -
                EntityTraits<u32>::s_index_bits;

    for ( u32 i = 0; i < (1u << count) + 1; i++ ) {
        auto result = factory.acquire();
        auto entity = result.item();

        if ( result.is_fail() )
            break;

        printf("entity(%10u) = {index %8u, epoch %3u}\n",
            entity,
            decode(entity).index,
            decode(entity).epoch);

        factory.release(entity);
    }

    return 0;
}
