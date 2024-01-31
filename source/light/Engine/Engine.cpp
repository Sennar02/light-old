#include <light/Engine/Engine.hpp>

namespace lgh
{
    static sf::Clock g_clock;

    Engine::Engine()
        : m_machine {}
        , m_state {0}
    { }

    Result<bool, fail::Insert>
    Engine::program(const String& name, State& state)
    {
        return m_machine.insert(name, state);
    }

    bool
    Engine::execute(const String& name, u32 frames)
    {
        sf::Time slice = sf::seconds(1.f / frames);
        sf::Time delta;

        if ( m_machine.table().contains(name) == false )
            return false;

        m_state = start(name);

        while ( m_state != 0 ) {
            if ( input() == 0 ) break;

            for ( ; delta >= slice; delta -= slice )
                fixed_step(slice.asSeconds());

            after_step();

            delta += g_clock.restart();
        }

        clean();

        return true;
    }

    State*
    Engine::start(const String& name)
    {
        auto func = [](State*& state, auto) {
            state->start();
        };

        m_machine.table().for_each(func);

        return m_machine.launch(name);
    }

    void
    Engine::clean()
    {
        auto func = [](State*& state, auto) {
            state->clean();
        };

        m_machine.table().for_each(func);
    }

    State*
    Engine::input()
    {
        String next = m_state->next;

        if ( m_state->input() == false ) {
            m_state->next = "";

            m_state =
                m_machine.launch(next);
        }

        return m_state;
    }

    void
    Engine::fixed_step(f32 delta)
    {
        auto func = [delta](State*& state, auto) {
            state->fixed_step(delta);
        };

        m_machine.table().for_each(func);
    }

    void
    Engine::after_step()
    {
        auto func = [](State*& state, auto) {
            state->after_step();
        };

        m_machine.table().for_each(func);
    }
} // namespace lgh
