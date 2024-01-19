#ifndef LIGHT_BASE_RESULT_HPP
#define LIGHT_BASE_RESULT_HPP

namespace lgt
{
    template <class Succ, class Fail>
    class Result
    {
    public:
        /**
         *
         */
        Result(const Succ& succ);

        /**
         *
         */
        Result(const Fail& fail);

        /**
         *
         */
        bool
        is_succ() const;

        /**
         *
         */
        bool
        is_succ(const Succ& succ) const;

        /**
         *
         */
        bool
        is_fail() const;

        /**
         *
         */
        bool
        is_fail(const Fail& fail) const;

        /**
         *
         */
        const Succ&
        succ(const Succ& deflt) const;

        /**
         *
         */
        Succ&
        succ(Succ& deflt);

        /**
         *
         */
        Fail
        fail() const;

    private:
        union
        {
            /**
             *
             */
            Succ m_succ;

            /**
             *
             */
            Fail m_fail;
        };

        /**
         *
         */
        bool m_valid;
    };

    template <class Succ, class Fail>
    class Result<Succ&, Fail>
    {
    public:
        /**
         *
         */
        Result(Succ& succ);

        /**
         *
         */
        Result(const Fail& fail);

        /**
         *
         */
        bool
        is_succ() const;

        /**
         *
         */
        bool
        is_succ(const Succ& succ) const;

        /**
         *
         */
        bool
        is_fail() const;

        /**
         *
         */
        bool
        is_fail(const Fail& fail) const;

        /**
         *
         */
        const Succ&
        succ(const Succ& deflt) const;

        /**
         *
         */
        Succ&
        succ(Succ& deflt);

        /**
         *
         */
        Fail
        fail() const;

    private:
        union
        {
            /**
             *
             */
            Succ* m_succ;

            /**
             *
             */
            Fail m_fail;
        };

        /**
         *
         */
        bool m_valid;
    };
} // namespace lgt

#include <light/Base/inline/Result.inl>

#endif // LIGHT_BASE_RESULT_HPP
