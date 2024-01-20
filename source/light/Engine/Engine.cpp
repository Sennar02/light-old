#include <light/Engine/Engine.hpp>

namespace lgt
{
    using sf::Clock;

    static Clock   g_clock;
    static System* g_buffer[g_KiB] = {0};

    Engine::Engine()
        : m_queue {g_buffer, g_KiB}
    { }

    Result<bool, fail::Insert>
    Engine::insert(System& system)
    {
        if ( system.accept(this) )
            return m_queue.insert(&system);

        return false;
    }

    bool
    Engine::loop(u32 frames)
    {
        sf::Time slice = sf::seconds(1.f / frames);
        sf::Time delta = g_clock.getElapsedTime();

        enter();

        while ( true ) {
            delta += g_clock.getElapsedTime();

            for ( ; delta < slice; delta -= slice )
                fixed_step(slice.asSeconds());

            after_step();
        }

        leave();

        return true;
    }

    void
    Engine::enter()
    {
        auto func = [](System*& system, u32) {
            system->enter();
        };

        m_queue.for_each(func);
    }

    void
    Engine::leave()
    {
        auto func = [](System*& system, u32) {
            system->leave();
        };

        m_queue.for_each(func);
    }

    void
    Engine::fixed_step(f32 delta)
    {
        auto func = [delta](System*& system, u32) {
            system->fixed_step(delta);
        };

        m_queue.for_each(func);
    }

    void
    Engine::after_step()
    {
        auto func = [](System*& system, u32) {
            system->after_step();
        };

        m_queue.for_each(func);
    }
} // namespace lgt
