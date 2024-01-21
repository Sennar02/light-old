#include <light/Algo/import.hpp>
#include <time.h>
#include <stdio.h>

using namespace lgt;

template <class Item, class Layout>
void
print_table(const HashTable<Item, Layout>& table)
{
    auto& heads = table.heads();
    auto& array = table.array();

    for ( u32 i = 0; i < table.size(); i++ ) {
        if ( heads[i].dist != 0 )
            printf("%3u. \x1b[34mdist %3u, link %3u => %3u => %3u\x1b[0m ",
                i,
                heads[i].dist,
                heads[i].link,
                array[heads[i].link].link,
                heads[array[heads[i].link].link].link);
        else
            printf("%3u. \x1b[33mdist ---, link -----------------\x1b[0m ", i);

        if ( i < table.count() )
            printf("| \x1b[34mlink %3u => %3u => %3u, name %3u, item %3u\x1b[0m\n",
                array[i].link,
                heads[array[i].link].link,
                array[heads[array[i].link].link].link,
                array[i].name,
                array[i].item);
        else
            printf("| \x1b[33mlink -----------------, name ---, item ---\x1b[0m\n");
    }
}

static const u32 g_count = 8u;

int
main(int, const char*[])
{
    ArenaOrigin origin = {calloc(1u, g_MiB), g_MiB};

    HashTable<u32, u32> table = {origin, g_count};

    srand(time(0));

    printf("Populating...\n");

    for ( u32 i = 0; i < g_count * 1.5f; i++ ) {
        u32  name   = rand() % (g_count * 2u);
        u32  item   = rand() % (g_count * 2u);
        auto result = table.insert(name, item);

        if ( result.is_succ() )
            printf("\x1b[32msuccess from (%3u, %3u)\x1b[0m\n", name, item);
        else
            printf("\x1b[31mfailure from (%3u, %3u): %s\x1b[0m\n",
                name,
                item,
                fail::g_insert[result.fail()]);
    }

    printf("\nTable state:\n");

    print_table(table);

    printf("\nFor each loop:\n");

    table.for_each([](u32& item, const u32& name) {
        printf("%3u := %3u\n", name, item);
    });

    return 0;
}
