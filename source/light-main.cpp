#include <light/Algo/import.hpp>
#include <time.h>
#include <stdio.h>

using namespace lgh;

template <class Item, class Layout>
void
print_table(const HashTable<Item, Layout>& table)
{
    auto& heads = table.heads();
    auto& array = table.array();

    for ( u32 i = 0; i < heads.length(); i++ ) {
        if ( heads[i].dist != 0 ) {
            if ( heads[i].link == heads[array[heads[i].link].link].link )
                printf("%3u. \x1b[34mdist %3u, link %3u\x1b[0m ",
                    i,
                    heads[i].dist,
                    heads[i].link);
            else
                printf("%3u. \x1b[31mdist %3u, link %3u\x1b[0m ",
                    i,
                    heads[i].dist,
                    heads[i].link);
        } else
            printf("%3u. \x1b[33mdist ---, link ---\x1b[0m ", i);

        if ( i < table.count() ) {
            if ( array[i].link == array[heads[array[i].link].link].link )
                printf("| \x1b[34mlink %3u, name %3u, item %3u\x1b[0m\n",
                    array[i].link,
                    array[i].name,
                    array[i].item);
            else
                printf("| \x1b[31mlink %3u, name %3u, item %3u\x1b[0m\n",
                    array[i].link,
                    array[i].name,
                    array[i].item);
        } else
            printf("| \x1b[33mlink ---, name ---, item ---\x1b[0m\n");
    }
}

static const u32 g_count = 48u;

int
main(int, const char*[])
{
    HashTable<u32, u32> table;

    Array<HashHead>           heads = {g_origin, g_count * 2u};
    Array<HashBody<u32, u32>> array = {g_origin, g_count};

    if ( table.build(heads, array) == false )
        return 1;

    srand(time(0));

    for ( u32 i = 0; i < g_count * 1.5f; i++ ) {
        u32 name = rand() % (g_count * 3u);
        u32 item = rand() % (g_count * 3u);

        table.insert(name, item);
    }

    print_table(table);

    return 0;
}
