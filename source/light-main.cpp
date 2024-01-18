#include <light/Memory/import.hpp>
#include <stdio.h>

using namespace lgt;

static char g_memory[g_KiB] = {0};

int
main(int, const char*[])
{
    PoolOrigin origin = {g_memory, 72u, 64u};

    u32   length = origin.assures(2u);
    auto  result = origin.acquire(length);
    char* memory = result.value(0);

    if (result.is_error() == true) {
        printf("[\x1b[31mERR\x1b[0m]: %s\n",
            err::g_acquire[result.error()]);

        return 1;
    } else
        printf("%p, %u\n",
            memory,
            origin.release(memory).is_value());

    return 0;
}
