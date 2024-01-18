#include <light/Base/Vect2d.hpp>

namespace lgt
{
    template <class Type>
    Vect2d<Type>::Vect2d()
        : m_memory {}
    { }

    template <class Type>
    Vect2d<Type>::Vect2d(const Type& x, const Type& y)
        : m_memory {x, y}
    { }

    template <class Type>
    Vect2d<Type>::Vect2d(const Type& x)
        : m_memory {x, x}
    { }

    template <class Type>
    Type
    Vect2d<Type>::operator[](u32 index) const
    {
        if ( index < s_size )
            return m_memory[index];

        return {};
    }

    template <class Type>
    template <class Othr>
    Vect2d<Type>
    Vect2d<Type>::operator+(const Vect2d<Othr>& other) const
    {
        return {
            m_memory[0] + other.m_memory[0],
            m_memory[1] + other.m_memory[1],
        };
    }

    template <class Type>
    template <class Othr>
    Vect2d<Type>
    Vect2d<Type>::operator+(const Othr& other) const
    {
        return {
            m_memory[0] + other,
            m_memory[1] + other,
        };
    }

    template <class Type>
    template <class Othr>
    Vect2d<Type>
    Vect2d<Type>::operator*(const Vect2d<Othr>& other) const
    {
        return {
            m_memory[0] * other.m_memory[0],
            m_memory[1] * other.m_memory[1],
        };
    }

    template <class Type>
    template <class Othr>
    Vect2d<Type>
    Vect2d<Type>::operator*(const Othr& other) const
    {
        return {
            m_memory[0] * other,
            m_memory[1] * other,
        };
    }

    template <class Type>
    template <class Othr>
    Vect2d<Type>
    Vect2d<Type>::operator-(const Vect2d<Othr>& other) const
    {
        return {
            m_memory[0] - other.m_memory[0],
            m_memory[1] - other.m_memory[1],
        };
    }

    template <class Type>
    template <class Othr>
    Vect2d<Type>
    Vect2d<Type>::operator-(const Othr& other) const
    {
        return {
            m_memory[0] - other,
            m_memory[1] - other,
        };
    }

    template <class Type>
    template <class Othr>
    Vect2d<Type>
    Vect2d<Type>::operator/(const Vect2d<Othr>& other) const
    {
        return {
            m_memory[0] / other.m_memory[0],
            m_memory[1] / other.m_memory[1],
        };
    }

    template <class Type>
    template <class Othr>
    Vect2d<Type>
    Vect2d<Type>::operator/(const Othr& other) const
    {
        return {
            m_memory[0] / other,
            m_memory[1] / other,
        };
    }
} // namespace lgt
