#ifndef LIGHT_BASE_TRAITS_REMOVE_PTR_HPP
#define LIGHT_BASE_TRAITS_REMOVE_PTR_HPP

namespace lgh
{
    namespace impl
    {
        template <class Type>
        struct RemovePtr {
            using Main = Type;
        };

        template <class Type>
        struct RemovePtr<Type*> {
            using Main = Type;
        };
    } // namespace impl

    template <class Type>
    using RemovePtr = typename impl::RemovePtr<Type>::Main;
} // namespace lgh

#endif // LIGHT_BASE_TRAITS_REMOVE_PTR_HPP
