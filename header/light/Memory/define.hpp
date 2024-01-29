#ifndef LIGHT_MEMORY_DEFINE_HPP
#define LIGHT_MEMORY_DEFINE_HPP

#include <light/Memory/depend.hpp>

namespace lgh
{
    /**
     *
     */
    class BaseOrigin;
    class PoolOrigin;
    class TreeOrigin;
    class ArenaOrigin;
    class StackOrigin;
    class EmptyOrigin;
    class KernOrigin;

    namespace fail
    {
        enum Acquire
        {
            NotEnoughMemory,
            AlignmentFiasco,
            NoByteRequested,
        };

        static const char* const g_acquire[] = {
            "Acquire::NotEnoughMemory",
            "Acquire::AlignmentFiasco",
            "Acquire::NoByteRequested",
        };

        enum Release
        {
            AlreadyReleased,
            NotMemoryParent,
        };

        static const char* const g_release[] = {
            "Release::AlreadyReleased",
            "Release::NotMemoryParent",
        };
    } // namespace fail

    /**
     * Memory layouts which are responsible
     * for their own memory and must expose
     * at least the following interface:
     *
     * bool   | resize(u32 items, u32 scale);
     * u32    | length(u32 scale) const;
     * char & |   find(u32 index, u32 scale) const;
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
    class Array2D;

    static const u32 g_KiB = 1024u;
    static const u32 g_MiB = g_KiB * g_KiB;
    static const u32 g_GiB = g_MiB * g_KiB;

    static const u32 g_KB = 1000u;
    static const u32 g_MB = g_KB * g_KB;
    static const u32 g_GB = g_MB * g_KB;

    extern KernOrigin g_origin;
} // namespace lgh

#endif // LIGHT_MEMORY_DEFINE_HPP
