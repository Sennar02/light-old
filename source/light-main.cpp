#include <light/Algo/import.hpp>
#include <stdio.h>

using namespace lgt;

static char g_memory[g_KiB] = {0};

int
main(int, const char*[])
{
    ArenaOrigin origin = {g_memory, g_KiB};

    HashTable<String, int> table = {origin, 8u};

    printf("%u\n", table.insert(LGT_STRING("Hello"), 5).is_succ());
    printf("%u\n", table.insert(LGT_STRING("Main"), 4).is_succ());
    printf("%u\n", table.insert(LGT_STRING("Function"), 8).is_succ());

    table
        .for_each([](int& x, const String& y) {
            printf("%s := %i\n", y.memory(), x);
        })
        .clear();

    return 0;
}
