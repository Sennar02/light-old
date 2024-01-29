#include <light/Base/Vector.hpp>

namespace lgh
{
    template <class Type, u32 Size>
    Vector<Type, Size>::Vector()
        : m_data {}
    { }

    template <class Type, u32 Size>
    template <class... Args>
    Vector<Type, Size>::Vector(Args... args)
        : m_data {((Type) args)...}
    { }

    template <class Type, u32 Size>
    Vector<Type, Size>::Vector(const Type& value)
        : m_data {}
    {
        for ( u32 i = 0; i < s_size; i++ )
            m_data[i] = value;
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
            if ( m_data[i] != other.m_data[i] )
                return false;
        }

        return true;
    }
} // namespace lgh
