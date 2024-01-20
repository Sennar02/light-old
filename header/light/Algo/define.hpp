#ifndef LIGHT_ALGO_DEFINE_HPP
#define LIGHT_ALGO_DEFINE_HPP

#include <light/Algo/depend.hpp>

namespace lgt
{
    namespace fail
    {
        enum Insert
        {
            NotEnoughSpace,
            NameRepetition,
        };

        static const char* const g_insert[] = {
            LGT_AS_STRING(Insert::NotEnoughSpace).memory(),
            LGT_AS_STRING(Insert::NameRepetition).memory(),
        };

        enum Remove
        {
            UnknownElement,
            AlreadyRemoved,
        };

        static const char* const g_remove[] = {
            LGT_AS_STRING(Remove::UnknownElement).memory(),
            LGT_AS_STRING(Remove::AlreadyRemoved).memory(),
        };
    } // namespace fail

    template <class Item, class Layout>
    class ArrayList;

    template <class Item, class Layout>
    class ArrayDeque;

    template <class Name, class Item, class Layout>
    class HashTable;
} // namespace lgt

#endif // LIGHT_ALGO_DEFINE_HPP
