#ifndef LIGHT_BASE_TRAITS_REMOVE_REF_HPP
#define LIGHT_BASE_TRAITS_REMOVE_REF_HPP

namespace lgh
{
    namespace impl
    {
        template <class Type>
        struct RemoveRef {
            using Main = Type;
        };

        template <class Type>
        struct RemoveRef<Type&> {
            using Main = Type;
        };

        template <class Type>
        struct RemoveRef<Type&&> {
            using Main = Type;
        };
    } // namespace impl

    template <class Type>
    using RemoveRef = typename impl::RemoveRef<Type>::Main;
} // namespace lgh

#endif // LIGHT_BASE_TRAITS_REMOVE_REF_HPP
