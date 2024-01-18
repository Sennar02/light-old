#ifndef LIGHT_BASE_VECT_2D_HPP
#define LIGHT_BASE_VECT_2D_HPP

#include <light/Base/define.hpp>

namespace lgt
{
    template <class Type>
    class Vect2d
    {
    public:
        /**
         *
         */
        static const u32 s_size = 2u;

    public:
        /**
         *
         */
        Vect2d();

        /**
         *
         */
        Vect2d(const Type& x, const Type& y);

        /**
         *
         */
        Vect2d(const Type& x);

        /**
         *
         */
        Type
        operator[](u32 index) const;

        /**
         *
         */
        template <class Othr>
        Vect2d<Type>
        operator+(const Vect2d<Othr>& other) const;

        /**
         *
         */
        template <class Othr>
        Vect2d<Type>
        operator+(const Othr& other) const;

        /**
         *
         */
        template <class Othr>
        Vect2d<Type>
        operator*(const Vect2d<Othr>& other) const;

        /**
         *
         */
        template <class Othr>
        Vect2d<Type>
        operator*(const Othr& other) const;

        /**
         *
         */
        template <class Othr>
        Vect2d<Type>
        operator-(const Vect2d<Othr>& other) const;

        /**
         *
         */
        template <class Othr>
        Vect2d<Type>
        operator-(const Othr& other) const;

        /**
         *
         */
        template <class Othr>
        Vect2d<Type>
        operator/(const Vect2d<Othr>& other) const;

        /**
         *
         */
        template <class Othr>
        Vect2d<Type>
        operator/(const Othr& other) const;

    private:
        /**
         *
         */
        Type m_memory[s_size];
    };

    using Vect2u = Vect2d<u32>;
    using Vect2i = Vect2d<i32>;
    using Vect2f = Vect2d<f32>;
} // namespace lgt

#endif // LIGHT_BASE_VECT_2D_HPP
