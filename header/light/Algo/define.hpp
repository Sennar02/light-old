#ifndef LIGHT_ALGO_DEFINE_HPP
#define LIGHT_ALGO_DEFINE_HPP

#include <light/Algo/depend.hpp>

namespace lgh
{
    namespace fail
    {
        enum Insert
        {
            NotEnoughSpace,
            NameRepetition,
            InvalidElement,
        };

        static const char* const g_insert[] = {
            "Insert::NotEnoughSpace",
            "Insert::NameRepetition",
            "Insert::InvalidElement",
        };

        enum Remove
        {
            UnknownElement,
            AlreadyRemoved,
        };

        static const char* const g_remove[] = {
            "Remove::UnknownElement",
            "Remove::AlreadyRemoved",
        };
    } // namespace fail

    template <class Item, class Layout>
    class ArrayList;

    template <class Item, class Layout>
    class ArrayDeque;

    template <class Name, class Item, class Layout>
    class HashTable;

    class ForwIterator;
    class BackIterator;
} // namespace lgh

#endif // LIGHT_ALGO_DEFINE_HPP
