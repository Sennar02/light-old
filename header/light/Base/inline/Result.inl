#include <light/Base/Result.hpp>

namespace lgt
{
    template <class Succ, class Fail>
    Result<Succ, Fail>::Result(const Succ& succ)
        : m_succ {succ}
        , m_valid {true}
    { }

    template <class Succ, class Fail>
    Result<Succ, Fail>::Result(const Fail& fail)
        : m_fail {fail}
        , m_valid {false}
    { }

    template <class Succ, class Fail>
    bool
    Result<Succ, Fail>::is_succ() const
    {
        return m_valid;
    }

    template <class Succ, class Fail>
    bool
    Result<Succ, Fail>::is_succ(const Succ& succ) const
    {
        if ( m_valid && m_succ == succ )
            return true;

        return false;
    }

    template <class Succ, class Fail>
    bool
    Result<Succ, Fail>::is_fail() const
    {
        return m_valid == false;
    }

    template <class Succ, class Fail>
    bool
    Result<Succ, Fail>::is_fail(const Fail& fail) const
    {
        if ( m_valid || m_fail != fail )
            return false;

        return true;
    }

    template <class Succ, class Fail>
    const Succ&
    Result<Succ, Fail>::succ(const Succ& deflt) const
    {
        if ( m_valid )
            return m_succ;

        return deflt;
    }

    template <class Succ, class Fail>
    Succ&
    Result<Succ, Fail>::succ(Succ& deflt)
    {
        if ( m_valid )
            return m_succ;

        return deflt;
    }

    template <class Succ, class Fail>
    Fail
    Result<Succ, Fail>::fail() const
    {
        if ( m_valid )
            return {};

        return m_fail;
    }

    template <class Succ, class Fail>
    Result<Succ&, Fail>::Result(Succ& succ)
        : m_succ {&succ}
        , m_valid {true}
    { }

    template <class Succ, class Fail>
    Result<Succ&, Fail>::Result(const Fail& fail)
        : m_fail {fail}
        , m_valid {false}
    { }

    template <class Succ, class Fail>
    bool
    Result<Succ&, Fail>::is_succ() const
    {
        return m_valid;
    }

    template <class Succ, class Fail>
    bool
    Result<Succ&, Fail>::is_succ(const Succ& succ) const
    {
        if ( m_valid && *m_succ == succ )
            return true;

        return false;
    }

    template <class Succ, class Fail>
    bool
    Result<Succ&, Fail>::is_fail() const
    {
        return m_valid == false;
    }

    template <class Succ, class Fail>
    bool
    Result<Succ&, Fail>::is_fail(const Fail& fail) const
    {
        if ( m_valid || *m_fail != fail )
            return false;

        return true;
    }

    template <class Succ, class Fail>
    const Succ&
    Result<Succ&, Fail>::succ(const Succ& deflt) const
    {
        if ( m_valid )
            return *m_succ;

        return deflt;
    }

    template <class Succ, class Fail>
    Succ&
    Result<Succ&, Fail>::succ(Succ& deflt)
    {
        if ( m_valid )
            return *m_succ;

        return deflt;
    }

    template <class Succ, class Fail>
    Fail
    Result<Succ&, Fail>::fail() const
    {
        if ( m_valid )
            return {};

        return m_fail;
    }
} // namespace lgt
