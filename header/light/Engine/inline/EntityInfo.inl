#include <light/Engine/EntityInfo.hpp>

namespace lgh
{
    template <class Type>
    EntityInfo<Type>
    decode(Type entity)
    {
        Type bits = EntityTraits<Type>::s_index_bits;

        Type index = entity & ((1u << bits) - 1u);
        Type epoch = entity - index;

        return {index, (epoch >> bits)};
    }

    template <class Type>
    Type
    encode(EntityInfo<Type> info)
    {
        Type bits = EntityTraits<Type>::s_index_bits;

        if ( info.index >= 1u << (bits + 1u) )
            info.index = 0;

        return {info.index + (info.epoch << bits)};
    }
} // namespace lgh
