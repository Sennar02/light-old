#ifndef LIGHT_BASE_VEC_2D_HPP
#define LIGHT_BASE_VEC_2D_HPP

#include <light/Base/define.hpp>

namespace lgh
{
    template <class Type>
    class Vec2d
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
        Vec2d();

        /**
         *
         */
        Vec2d(const Type& x, const Type& y);

        /**
         *
         */
        Vec2d(const Type& x);

        /**
         *
         */
        Type
        operator[](u32 index) const;

        /**
         *
         */
        template <class Othr>
        Vec2d<Type>
        operator+(const Vec2d<Othr>& other) const;

        /**
         *
         */
        template <class Othr>
        Vec2d<Type>
        operator+(const Othr& other) const;

        /**
         *
         */
        template <class Othr>
        Vec2d<Type>
        operator*(const Vec2d<Othr>& other) const;

        /**
         *
         */
        template <class Othr>
        Vec2d<Type>
        operator*(const Othr& other) const;

        /**
         *
         */
        template <class Othr>
        Vec2d<Type>
        operator-(const Vec2d<Othr>& other) const;

        /**
         *
         */
        template <class Othr>
        Vec2d<Type>
        operator-(const Othr& other) const;

        /**
         *
         */
        template <class Othr>
        Vec2d<Type>
        operator/(const Vec2d<Othr>& other) const;

        /**
         *
         */
        template <class Othr>
        Vec2d<Type>
        operator/(const Othr& other) const;

    private:
        /**
         *
         */
        Type m_memory[s_size];
    };

    using Vec2u = Vec2d<u32>;
    using Vec2i = Vec2d<i32>;
    using Vec2f = Vec2d<f32>;
} // namespace lgh

#include <light/Base/inline/Vec2d.inl>

#endif // LIGHT_BASE_VEC_2D_HPP
