#ifndef LIGHT_ALGO_BACK_ITERATOR_HPP
#define LIGHT_ALGO_BACK_ITERATOR_HPP

#include <light/Algo/define.hpp>

namespace lgh
{
    class BackIterator
    {
    public:
        /**
         *
         */
        BackIterator();

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

#endif // LIGHT_ALGO_BACK_ITERATOR_HPP
