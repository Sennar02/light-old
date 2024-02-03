#ifndef LIGHT_BASE_VECTOR_HPP
#define LIGHT_BASE_VECTOR_HPP

#include <light/Base/define.hpp>

namespace lgh
{
    template <class Type, u32 Size>
    class Vector
    {
    public:
        /**
         *
         */
        static const u32 s_size = Size;

    public:
        /**
         *
         */
        Vector();

        /**
         *
         */
        template <class... Args>
        Vector(Args... args);

        /**
         *
         */
        template <class Othr>
        Vector(const Vector<Othr, Size>& other);

        /**
         *
         */
        Vector<Type, Size>
        absolute() const;

        /**
         *
         */
        Vector<Type, Size>
        normal() const;

        /**
         *
         */
        Type
        strength() const;

        /**
         *
         */
        Type&
        operator[](u32 index);

        /**
         *
         */
        const Type&
        operator[](u32 index) const;

        /**
         *
         */
        template <class Othr>
        Vector<Type, Size>
        operator+(const Vector<Othr, Size>& other) const;

        /**
         *
         */
        template <class Othr>
        Vector<Type, Size>
        operator+(const Othr& other) const;

        /**
         *
         */
        template <class Othr>
        Vector<Type, Size>
        operator*(const Vector<Othr, Size>& other) const;

        /**
         *
         */
        template <class Othr>
        Vector<Type, Size>
        operator*(const Othr& other) const;

        /**
         *
         */
        template <class Othr>
        Vector<Type, Size>
        operator-(const Vector<Othr, Size>& other) const;

        /**
         *
         */
        template <class Othr>
        Vector<Type, Size>
        operator-(const Othr& other) const;

        /**
         *
         */
        template <class Othr>
        Vector<Type, Size>
        operator/(const Vector<Othr, Size>& other) const;

        /**
         *
         */
        template <class Othr>
        Vector<Type, Size>
        operator/(const Othr& other) const;

        /**
         *
         */
        template <class Othr>
        bool
        operator==(const Vector<Othr, Size>& other) const;

        /**
         *
         */
        template <class Othr>
        bool
        operator!=(const Vector<Othr, Size>& other) const;

    private:
        /**
         *
         */
        Type m_data[s_size];
    };
} // namespace lgh

#include <light/Base/inline/Vector.inl>

#endif // LIGHT_BASE_VECTOR_HPP
