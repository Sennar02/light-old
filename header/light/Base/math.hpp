#ifndef LIGHT_BASE_MATH_HPP
#define LIGHT_BASE_MATH_HPP

#include <light/Base/define.hpp>

namespace lgt
{
    template <class Type, class Else = Type>
    constexpr Type
    max(Type value, Else other);

    template <class Type, class Else = Type>
    constexpr Type
    min(Type value, Else other);

    template <class Type, class Else>
    constexpr Type
    floor(Type value, Else other);

    template <class Type, class Else>
    constexpr Type
    ceil(Type value, Else other);

    template <class Type>
    struct Hash
    {
        constexpr static u32
        code(const Type& value);
    };

    template <class Type>
    struct Compare
    {
        constexpr static bool
        equals(const Type& value, const Type& other);
    };

} // namespace lgt

#include <light/Base/inline/math.inl>

#endif // LIGHT_BASE_MATH_HPP
