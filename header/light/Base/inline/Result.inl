#include <light/Base/Result.hpp>

namespace lgt
{
    template <class Type, class Else>
    Result<Type, Else>::Result(const Type& value)
        : m_value {value}
        , m_valid {true}
    { }

    template <class Type, class Else>
    Result<Type, Else>::Result(Else error)
        : m_error {error}
        , m_valid {false}
    { }

    template <class Type, class Else>
    bool
    Result<Type, Else>::is_value() const
    {
        return m_valid;
    }

    template <class Type, class Else>
    bool
    Result<Type, Else>::is_error() const
    {
        return m_valid == false;
    }

    template <class Type, class Else>
    template <class Item, class... Rest>
    bool
    Result<Type, Else>::is_error(Item error, Rest... other) const
    {
        if ( m_valid ) return false;

        if ( m_error != error ) {
            if constexpr ( sizeof...(Rest) != 0 )
                return is_error(other...);
        } else
            return true;

        return false;
    }

    template <class Type, class Else>
    const Type&
    Result<Type, Else>::value(const Type& deflt) const
    {
        if ( m_valid )
            return m_value;

        return deflt;
    }

    template <class Type, class Else>
    Type&
    Result<Type, Else>::value(Type& deflt) const
    {
        if ( m_valid )
            return m_value;

        return deflt;
    }

    template <class Type, class Else>
    Else
    Result<Type, Else>::error() const
    {
        if ( m_valid == false )
            return m_error;

        return {};
    }
} // namespace lgt
