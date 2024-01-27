#include <light/Engine/import.hpp>
#include <stdio.h>

using namespace lgh;

class MainState
    : public State
{
public:
    MainState()
        : m_window {}
    { }

    void
    start()
    {
        m_window.create(sf::VideoMode {1280, 720}, "Light");
    }

    void
    clean()
    {
        m_window.close();
    }

    bool
    input()
    {
        sf::Event event;

        while ( m_window.pollEvent(event) ) {
            if ( event.type == sf::Event::Closed )
                return false;

            if ( event.type == sf::Event::KeyReleased ) {
                if ( event.key.code == sf::Keyboard::Escape )
                    return false;
            }
        }

        return true;
    }

private:
    sf::RenderWindow m_window;
};

int
main(int, const char*[])
{
    Engine    engine;
    MainState title;

    engine.program("MainState", title);
    engine.execute("MainState");

    return 0;
}
