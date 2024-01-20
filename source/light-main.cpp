#include <light/Engine/import.hpp>
#include <stdio.h>

using namespace lgt;

class WindowSystem
    : public System
{
public:
    WindowSystem()
        : m_window {}
    { }

    bool
    accept(void*)
    {
        return true;
    }

    void
    enter()
    {
        m_window.create(sf::VideoMode {1280, 720}, "Light");
        m_window.clear();
    }

    void
    after_step()
    {
        sf::Event event;

        while ( m_window.pollEvent(event) ) {
            if ( event.type == sf::Event::Closed )
                // send exit event
                exit(0);

            if ( event.type == sf::Event::KeyReleased ) {
                if ( event.key.code == sf::Keyboard::Escape )
                    // send exit event
                    exit(0);
            }
        }

        m_window.display();
        m_window.clear();
    }

private:
    sf::RenderWindow m_window;
};

int
main(int, const char*[])
{
    // Engine       game;
    // WindowSystem window;

    // game.insert(window);
    // game.loop();

    EntityManager list;

    Entity def;
    auto   entity = list.acquire();

    if ( entity.is_fail() )
        return 1;

    def = entity.succ(def);

    printf("%u, %u\n",
        def.identif(),
        def.version());

    printf("%u\n", list.release(def).is_succ());

    return 0;
}
