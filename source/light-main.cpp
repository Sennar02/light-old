#include <light/Engine/import.hpp>
#include <stdio.h>

using namespace lgh;

static const u32 g_tile_size = 48u;              // pixels.
static const u32 g_tile_half = g_tile_size / 2u; // pixels.

static const Vector2u g_window_size = {32u, 18u};         // tiles.
static const Vector2u g_window_half = g_window_size / 2u; // tiles.
static const Vector2u g_camera_size = {32u, 18u};         // tiles.
static const Vector2u g_camera_half = g_camera_size / 2u; // tiles.
static const Vector2u g_world_size  = {32u, 96u};         // tiles.

static const u32 g_world_area = g_world_size[0] * g_world_size[1];

static const u32 g_colors_size = 3u;

static const sf::Color g_colors[g_colors_size] = {
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Blue,
};

struct Camera
{
    /**
     * Where the camera looks.
     */
    Vector2f target;

    /**
     * The distance from the target.
     *
     * This could be used to center
     * the target by setting a positive
     * offset of g_vport_half.
     */
    Vector2f offset;

    /**
     * Limits the camera shouldn't cross.
     */
    Vector2f border;
};

struct Player
{
    /**
     * Current position.
     */
    Vector2f position;

    /**
     * Unit vector used to keep
     * the movement direction.
     */
    Vector2f facing;

    /**
     * Position to reach.
     */
    Vector2f target;

    /**
     * Current speed.
     */
    f32 speed;

    /**
     * Maximum speed limit.
     */
    f32 speed_lim;

    /**
     * Whether it's moving or not.
     *
     * If position is equal to target,
     * this variable should be false.
     */
    bool moving;
};

class MainState
    : public State
{
public:
    MainState()
        : m_window {}
        , m_player {}
        , m_camera {}
        , m_world {g_origin, g_world_area, g_world_size[0]}
    { }

    void
    start()
    {
        auto mode = sf::VideoMode {
            g_window_size[0] * g_tile_size,
            g_window_size[1] * g_tile_size,
        };

        for ( u32 i = 0; i < g_world_area; i++ )
            m_world[i] = rand() % g_colors_size;

        m_window.create(mode, "Light");

        m_player.moving    = false;
        m_player.speed_lim = 10.f * g_tile_size;
        m_player.position  = {
            0.f * g_tile_size,
            0.f * g_tile_size,
        };

        m_camera.target = m_player.position;
        m_camera.border = {
            g_camera_size[0] * g_tile_size,
            g_camera_size[1] * g_tile_size,
        };
        m_camera.offset = {
            g_camera_half[0] * g_tile_size,
            g_camera_half[1] * g_tile_size,
        };
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

        if ( m_window.hasFocus() == false ) return true;

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

    void
    fixed_step(f32 delta)
    {
        const auto W = sf::Keyboard::W;
        const auto A = sf::Keyboard::A;
        const auto S = sf::Keyboard::S;
        const auto D = sf::Keyboard::D;

        if ( m_window.hasFocus() == false ) return;

        Vector2f distnc = {0.f, 0.f};
        Vector2f movemt = {0.f, 0.f};
        Vector2f target = {0.f, 0.f};
        Vector2f facing = {
            sf::Keyboard::isKeyPressed(D) - sf::Keyboard::isKeyPressed(A),
            sf::Keyboard::isKeyPressed(S) - sf::Keyboard::isKeyPressed(W),
        };

        if ( m_player.moving == false ) {
            if ( facing[0] != 0 || facing[1] != 0 ) {
                target = m_player.position + facing * g_tile_size;

                if ( target[0] >= 0 && target[0] < g_world_size[0] * g_tile_size ) {
                    m_player.target[0] = target[0];
                    m_player.facing[0] = facing[0];
                }

                if ( target[1] >= 0 && target[1] < g_world_size[1] * g_tile_size ) {
                    m_player.target[1] = target[1];
                    m_player.facing[1] = facing[1];
                }

                if ( (m_player.target == m_player.position) == false ) {
                    m_player.moving = true;
                    m_player.speed  = m_player.speed_lim;

                    if ( facing[0] != 0 && facing[1] != 0 )
                        m_player.speed /= M_SQRT2;
                }
            } else
                m_player.speed = 0.f;
        }

        if ( m_player.moving ) {
            movemt = m_player.facing * m_player.speed * delta;
            distnc = {
                abs(m_player.target[0] - m_player.position[0]),
                abs(m_player.target[1] - m_player.position[1]),
            };

            if ( abs(movemt[0]) > distnc[0] )
                m_player.position[0] = m_player.target[0];
            else
                m_player.position[0] += movemt[0];

            if ( abs(movemt[1]) > distnc[1] )
                m_player.position[1] = m_player.target[1];
            else
                m_player.position[1] += movemt[1];

            if ( m_player.position == m_player.target )
                m_player.moving = false;

            m_camera.target = m_player.position;
        }
    }

    void
    after_step()
    {
        sf::RectangleShape rect;

        rect.setSize({g_tile_size, g_tile_size});

        Vector2f diff = {
            (g_window_half[0] - g_camera_half[0]) * g_tile_size * 1.f,
            (g_window_half[1] - g_camera_half[1]) * g_tile_size * 1.f,
        };

        Vector2u base = {
            (u32) max((i32) ceil((m_camera.target[0] - m_camera.offset[0]) / g_tile_size) -1, 0),
            (u32) max((i32) ceil((m_camera.target[1] - m_camera.offset[1]) / g_tile_size) -1, 0),
        };

        Vector2u stop = {
            min((i32) ceil((m_camera.target[0] + m_camera.offset[0]) / g_tile_size) + 1, (i32) g_world_size[0]),
            min((i32) ceil((m_camera.target[1] + m_camera.offset[1]) / g_tile_size) + 1, (i32) g_world_size[1]),
        };

        printf("[%u, %u) x [%u, %u)\n",
            base[0],
            stop[0],
            base[1],
            stop[1]);

        m_window.clear();

        for ( u32 i = base[1]; i < stop[1]; i++ ) {
            for ( u32 j = base[0]; j < stop[0]; j++ ) {
                rect.setFillColor(g_colors[m_world[{j, i}]]);
                rect.setPosition({
                    j * g_tile_size - m_camera.target[0] + m_camera.offset[0] + diff[0],
                    i * g_tile_size - m_camera.target[1] + m_camera.offset[1] + diff[1],
                });

                m_window.draw(rect);
            }
        }

        rect.setFillColor(sf::Color::Magenta);
        rect.setPosition({
            m_player.position[0] - m_camera.target[0] + m_camera.offset[0] + diff[0],
            m_player.position[1] - m_camera.target[1] + m_camera.offset[1] + diff[1],
        });

        m_window.draw(rect);
        m_window.display();
    }

private:
    sf::RenderWindow m_window;
    Player           m_player;
    Camera           m_camera;
    Array2D<u32>     m_world;
};

int
main(int, const char*[])
{
    Engine    engine;
    MainState state;

    printf("%u\n", engine.program("MainState", state).is_item());

    if ( engine.execute("MainState") == false )
        return 1;

    return 0;
}
