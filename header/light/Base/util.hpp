#ifndef LIGHT_BASE_UTIL_HPP
#define LIGHT_BASE_UTIL_HPP

#include <light/Base/traits.hpp>

namespace lgt
{
    template <class Type>
    constexpr RemoveRef<Type>&&
    move(Type&& value);

    template <class Type>
    constexpr Type&&
    forw(RemoveRef<Type>& value);

    template <class Type>
    constexpr Type&&
    forw(RemoveRef<Type>&& value);

    template <class Type>
    constexpr void
    swap(Type& value, Type& other);

    template <class Type, class... Args>
    constexpr void
    ctor(Type& value, Args... args);

    template <class Type>
    constexpr void
    dtor(Type& value);

    template <class Type>
    constexpr auto&
    base(Type& value);

    template <class Type>
    auto
    decl() -> Type;
} // namespace lgt

#include <light/Base/inline/util.inl>

#endif // LIGHT_BASE_UTIL_HPP
