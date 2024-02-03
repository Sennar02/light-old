#include <light/Base/Vector.hpp>

namespace lgh
{
    template <class Type, u32 Size>
    Vector<Type, Size>::Vector()
        : m_data {0}
    { }

    template <class Type, u32 Size>
    template <class... Args>
    Vector<Type, Size>::Vector(Args... args)
        : m_data {((Type) args)...}
    { }

    template <class Type, u32 Size>
    template <class Othr>
    Vector<Type, Size>::Vector(const Vector<Othr, Size>& other)
        : m_data {0}
    {
        for ( u32 i = 0; i < s_size; i++ )
            m_data[i] = other[i];
    }

    template <class Type, u32 Size>
    Vector<Type, Size>
    Vector<Type, Size>::absolute() const
    {
        Vector<Type, Size> other;

        for ( u32 i = 0; i < s_size; i++ )
            other.m_data[i] = abs(m_data[i]);

        return other;
    }

    template <class Type, u32 Size>
    Vector<Type, Size>
    Vector<Type, Size>::normal() const
    {
        Vector<Type, Size> other;
        Type               value = strength();

        for ( u32 i = 0; i < s_size; i++ )
            other.m_data[i] = m_data[i] / value;

        return other;
    }

    template <class Type, u32 Size>
    Type
    Vector<Type, Size>::strength() const
    {
        Type value = 0;

        for ( u32 i = 0; i < s_size; i++ )
            value += m_data[i] * m_data[i];

        return sqrt(value);
    }

    template <class Type, u32 Size>
    Type&
    Vector<Type, Size>::operator[](u32 index)
    {
        return m_data[index];
    }

    template <class Type, u32 Size>
    const Type&
    Vector<Type, Size>::operator[](u32 index) const
    {
        return m_data[index];
    }

    template <class Type, u32 Size>
    template <class Othr>
    Vector<Type, Size>
    Vector<Type, Size>::operator+(const Vector<Othr, Size>& other) const
    {
        Vector<Type, Size> vect;

        for ( u32 i = 0; i < s_size; i++ )
            vect.m_data[i] = m_data[i] + other.m_data[i];

        return vect;
    }

    template <class Type, u32 Size>
    template <class Othr>
    Vector<Type, Size>
    Vector<Type, Size>::operator+(const Othr& other) const
    {
        Vector<Type, Size> vect;

        for ( u32 i = 0; i < s_size; i++ )
            vect.m_data[i] = m_data[i] + other;

        return vect;
    }

    template <class Type, u32 Size>
    template <class Othr>
    Vector<Type, Size>
    Vector<Type, Size>::operator*(const Vector<Othr, Size>& other) const
    {
        Vector<Type, Size> vect;

        for ( u32 i = 0; i < s_size; i++ )
            vect.m_data[i] = m_data[i] * other.m_data[i];

        return vect;
    }

    template <class Type, u32 Size>
    template <class Othr>
    Vector<Type, Size>
    Vector<Type, Size>::operator*(const Othr& other) const
    {
        Vector<Type, Size> vect;

        for ( u32 i = 0; i < s_size; i++ )
            vect.m_data[i] = m_data[i] * other;

        return vect;
    }

    template <class Type, u32 Size>
    template <class Othr>
    Vector<Type, Size>
    Vector<Type, Size>::operator-(const Vector<Othr, Size>& other) const
    {
        Vector<Type, Size> vect;

        for ( u32 i = 0; i < s_size; i++ )
            vect.m_data[i] = m_data[i] - other.m_data[i];

        return vect;
    }

    template <class Type, u32 Size>
    template <class Othr>
    Vector<Type, Size>
    Vector<Type, Size>::operator-(const Othr& other) const
    {
        Vector<Type, Size> vect;

        for ( u32 i = 0; i < s_size; i++ )
            vect.m_data[i] = m_data[i] - other;

        return vect;
    }

    template <class Type, u32 Size>
    template <class Othr>
    Vector<Type, Size>
    Vector<Type, Size>::operator/(const Vector<Othr, Size>& other) const
    {
        Vector<Type, Size> vect;

        for ( u32 i = 0; i < s_size; i++ )
            vect.m_data[i] = m_data[i] / other.m_data[i];

        return vect;
    }

    template <class Type, u32 Size>
    template <class Othr>
    Vector<Type, Size>
    Vector<Type, Size>::operator/(const Othr& other) const
    {
        Vector<Type, Size> vect;

        for ( u32 i = 0; i < s_size; i++ )
            vect.m_data[i] = m_data[i] / other;

        return vect;
    }

    template <class Type, u32 Size>
    template <class Othr>
    bool
    Vector<Type, Size>::operator==(const Vector<Othr, Size>& other) const
    {
        for ( u32 i = 0; i < s_size; i++ ) {
            if ( m_data[i] != other[i] )
                return false;
        }

        return true;
    }

    template <class Type, u32 Size>
    template <class Othr>
    bool
    Vector<Type, Size>::operator!=(const Vector<Othr, Size>& other) const
    {
        for ( u32 i = 0; i < s_size; i++ ) {
            if ( m_data[i] != other[i] )
                return true;
        }

        return false;
    }
} // namespace lgh
