#ifndef LIGHT_ALGO_FORW_ITERATOR_HPP
#define LIGHT_ALGO_FORW_ITERATOR_HPP

#include <light/Algo/define.hpp>

namespace lgh
{
    class ForwIterator
    {
    public:
        /**
         *
         */
        ForwIterator();

        /**
         *
         */
        bool
        has_next(u32 count) const;

        /**
         *
         */
        u32
        next(u32 count);

        /**
         *
         */
        void
        reset();

    private:
        /**
         *
         */
        u32 m_index;
    };
} // namespace lgh

#endif // LIGHT_ALGO_FORW_ITERATOR_HPP
