#ifndef LIGHT_ENGINE_ENTITY_INFO_HPP
#define LIGHT_ENGINE_ENTITY_INFO_HPP

#include <light/Engine/define.hpp>

namespace lgt
{
    using EntityType = u32;

    template <class Type>
    struct EntityTraits
    {
        static const u32 s_whole_bits = (sizeof(Type)) * 8u;
        static const u32 s_index_bits = (sizeof(Type) - 1) * 8u;
    };

    template <>
    struct EntityTraits<u32>
    {
        static const u32 s_whole_bits = sizeof(u32) * 8u;
        static const u32 s_index_bits = 27u;
    };

    template <class Type>
    struct EntityInfo
    {
        Type index;
        Type epoch;
    };

    /**
     *
     */
    template <class Type>
    EntityInfo<Type>
    decode(Type entity);

    /**
     *
     */
    template <class Type>
    Type
    encode(EntityInfo<Type> info);
} // namespace lgt

#include <light/Engine/inline/EntityInfo.inl>

#endif // LIGHT_ENGINE_ENTITY_INFO_HPP
