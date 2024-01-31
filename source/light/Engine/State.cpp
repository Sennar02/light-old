#include <light/Engine/State.hpp>

namespace lgh
{
    State::State()
        : next {}
    { }

    bool
    State::attach()
    {
        return true;
    }

    void
    State::start()
    { }

    void
    State::clean()
    { }

    void
    State::enter()
    { }

    void
    State::leave()
    { }

    bool
    State::input()
    {
        return true;
    }

    void
    State::fixed_step(f32)
    { }

    void
    State::after_step()
    { }
} // namespace lgh
