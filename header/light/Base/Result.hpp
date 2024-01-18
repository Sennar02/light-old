#ifndef LIGHT_BASE_RESULT_HPP
#define LIGHT_BASE_RESULT_HPP

namespace lgt
{
    template <class Type, class Else>
    class Result
    {
    public:
        /**
         *
         */
        Result(const Type& value);

        /**
         *
         */
        Result(Else error);

        /**
         *
         */
        bool
        is_value() const;

        /**
         *
         */
        bool
        is_error() const;

        /**
         *
         */
        template <class Item, class... Rest>
        bool
        is_error(Item error, Rest... other) const;

        /**
         *
         */
        const Type&
        value(const Type& deflt) const;

        /**
         *
         */
        Type&
        value(Type& deflt) const;

        /**
         *
         */
        Else
        error() const;

    private:
        union
        {
            /**
             *
             */
            Type m_value;

            /**
             *
             */
            Else m_error;
        };

        /**
         *
         */
        bool m_valid;
    };
} // namespace lgt

#include <light/Base/inline/Result.inl>

#endif // LIGHT_BASE_RESULT_HPP
