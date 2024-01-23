#ifndef LIGHT_MEMORY_DEFINE_HPP
#define LIGHT_MEMORY_DEFINE_HPP

#include <light/Memory/depend.hpp>

namespace lgh
{
    /**
     *
     */
    class BaseOrigin;
    class KernOrigin;
    class PoolOrigin;
    class TreeOrigin;
    class ArenaOrigin;
    class StackOrigin;
    class EmptyOrigin;

    namespace fail
    {
        enum Acquire
        {
            NotEnoughMemory,
            AlignmentFiasco,
            NoByteRequested,
        };

        static const char* const g_acquire[] = {
            LGT_AS_STRING(Acquire::NotEnoughMemory).memory(),
            LGT_AS_STRING(Acquire::AlignmentFiasco).memory(),
            LGT_AS_STRING(Acquire::NoByteRequested).memory(),
        };

        enum Release
        {
            AlreadyReleased,
            NotMemoryParent,
        };

        static const char* const g_release[] = {
            LGT_AS_STRING(Release::AlreadyReleased).memory(),
            LGT_AS_STRING(Release::NotMemoryParent).memory(),
        };
    } // namespace fail

    /**
     * Memory layouts which are responsible
     * for their own memory and must expose
     * at least the following interface:
     *
     * - u32 length(u32 scale) const;
     * - bool resize(u32 items, u32 scale);
     * - char& find(u32 index, u32 scale) const;
     */
    class FixedLayout;

    /**
     * Array of elements.
     */
    template <class Item, class Layout>
    class Array;

    /**
     * Two-dimensional array of elements.
     */
    template <class Item, class Layout>
    class Array2d;

    static const u32 g_KiB = 1024u;
    static const u32 g_MiB = g_KiB * g_KiB;
    static const u32 g_GiB = g_MiB * g_KiB;

    static const u32 g_KB = 1000u;
    static const u32 g_MB = g_KB * g_KB;
    static const u32 g_GB = g_MB * g_KB;

    extern ArenaOrigin g_origin;
} // namespace lgh

#endif // LIGHT_MEMORY_DEFINE_HPP
