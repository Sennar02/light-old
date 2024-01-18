#include <light/Base/util.hpp>

namespace lgt
{
    template <class Type>
    constexpr RemoveRef<Type>&&
    move(Type&& value)
    {
        return (RemoveRef<Type>&&) value;
    }

    template <class Type>
    constexpr Type&&
    forw(RemoveRef<Type>& value)
    {
        return (Type&&) value;
    }

    template <class Type>
    constexpr Type&&
    forw(RemoveRef<Type>&& value)
    {
        return (Type&&) value;
    }

    template <class Type>
    constexpr void
    swap(Type& value, Type& other)
    {
        Type temp = move(value);

        value = move(other);
        other = move(temp);
    }

    template <class Type, class... Args>
    constexpr void
    ctor(Type& value, Args... args)
    {
        new (&value) Type {forw<Args>(args)...};
    }

    template <class Type>
    constexpr void
    dtor(Type& value)
    {
        value.~Type();
    }

    template <class Type>
    constexpr auto&
    base(Type& value)
    {
        return (typename Type::Base&) value;
    }
} // namespace lgt
