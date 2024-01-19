#include <light/Base/math.hpp>

namespace lgt
{
    template <class Type, class Else>
    constexpr Type
    max(Type value, Else other)
    {
        if ( value < other )
            return other;

        return value;
    }

    template <class Type, class Else>
    constexpr Type
    min(Type value, Else other)
    {
        if ( other < value )
            return other;

        return value;
    }

    template <class Type, class Else>
    constexpr Type
    floor(Type value, Else other)
    {
        return value / other;
    }

    template <class Type, class Else>
    constexpr Type
    ceil(Type value, Else other)
    {
        if ( value % other != 0 )
            return value / other + 1;

        return value / other;
    }

    template <class Type>
    constexpr u32
    Hash<Type>::code(const Type& value)
    {
        return value.hash();
    }

    template <>
    constexpr u32
    Hash<u8>::code(const u8& value)
    {
        return value;
    }

    template <>
    constexpr u32
    Hash<i8>::code(const i8& value)
    {
        return value;
    }

    template <>
    constexpr u32
    Hash<u16>::code(const u16& value)
    {
        return value;
    }

    template <>
    constexpr u32
    Hash<i16>::code(const i16& value)
    {
        return value;
    }

    template <>
    constexpr u32
    Hash<u32>::code(const u32& value)
    {
        return value;
    }

    template <>
    constexpr u32
    Hash<i32>::code(const i32& value)
    {
        return value;
    }

    template <>
    constexpr u32
    Hash<char*>::code(char* const& value)
    {
        const char* str = value;
        u32         res = 5381u;

        if ( value == 0 ) return res;

        while ( u8 chr = *str++ ) {
            res = (res << 5u) + res;
            res = res ^ chr;
        }

        return res;
    }

    template <>
    constexpr u32
    Hash<const char*>::code(const char* const& value)
    {
        const char* str = value;
        u32         res = 5381u;

        if ( value == 0 ) return res;

        while ( u8 chr = *str++ ) {
            res = (res << 5u) + res;
            res = res ^ chr;
        }

        return res;
    }

    template <class Type>
    constexpr bool
    Compare<Type>::equals(const Type& value, const Type& other)
    {
        return value == other;
    }
} // namespace lgt
