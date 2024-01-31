#include <light/Engine/import.hpp>
#include <stdio.h>

using namespace lgh;

static const u32 g_tile_size = 96u;              // pixels.
static const u32 g_tile_half = g_tile_size / 2u; // pixels.

static const Vec2u g_window_size = {16u, 9u};          // tiles.
static const Vec2u g_window_half = g_window_size / 2u; // tiles.
static const Vec2u g_camera_size = {16u, 9u};          // tiles.
static const Vec2u g_camera_half = g_camera_size / 2u; // tiles.
static const Vec2u g_world_size  = {50u, 50u};         // tiles.

static const u32 g_world_area = g_world_size[0] * g_world_size[1];

static const u32 g_colors_size = 3u;

static const sf::Color g_colors[g_colors_size] = {
    {255u,    0,   0},
    {255u, 255u,   0},
    {255u,  96u, 32u},
};

struct Movement
{
    /**
     * Current position.
     */
    Vec2f position = {0, 0};

    /**
     * Position to reach.
     */
    Vec2f target = {0, 0};

    /**
     * Unit vector used to keep
     * the movement direction.
     */
    Vec2f orient = {0, 0};

    /**
     * Maximum speed.
     */
    f32 speed_max = 0;

    /**
     * Current speed.
     */
    f32 speed = 0;

    /**
     * Flag for movement tests.
     */
    bool moving = false;
};

void
movement(f32 delta, Vec2f orient, Movement& entity)
{
    Vec2f distance;
    Vec2f movement;

    if ( entity.moving ) {
        distance = (entity.target - entity.position).absolute();
        movement = entity.orient * entity.speed * delta;

        for ( u32 i = 0; i < movement.s_size; i++ ) {
            if ( abs(movement[i]) > distance[i] )
                entity.position[i] = entity.target[i];
            else
                entity.position[i] += movement[i];
        }

        if ( entity.position == entity.target )
            entity.moving = false;
    } else {
        if ( orient[0] != 0 || orient[1] != 0 ) {
            entity.target = entity.position + (orient * g_tile_size);
            entity.orient = orient;
            entity.moving = true;

            entity.speed = entity.speed_max / orient.strength();
        }
    }
}

struct Camera
{
    /**
     * Where the camera looks.
     */
    Vec2f target;

    /**
     * The distance from the target.
     *
     * This could be used to center
     * the target by setting a positive
     * offset of g_vport_half.
     */
    Vec2f offset;

    /**
     * Limits the camera shouldn't cross.
     */
    Vec2f border;
};

struct Entity
    : public Movement
{ };

class MainState
    : public State
{
public:
    MainState()
        : m_window {}
        , m_actors {g_origin, 10u}
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

        m_player.speed_max = 15.f * g_tile_size;
        m_player.position  = Vec2f {0, 0} * g_tile_size;

        for ( u32 i = 0; i < m_actors.length(); i++ ) {
            m_actors[i].position = {
                rand() % g_world_size[0] * g_tile_size,
                rand() % g_world_size[1] * g_tile_size,
            };

            m_actors[i].speed_max = rand() % 10u * g_tile_size * 1.f;
        }

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

        while ( m_window.pollEvent(event) ) {
            if ( event.type == sf::Event::Closed ) return false;

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

        Vec2f target = {0, 0};
        Vec2f orient = {
            sf::Keyboard::isKeyPressed(D) - sf::Keyboard::isKeyPressed(A),
            sf::Keyboard::isKeyPressed(S) - sf::Keyboard::isKeyPressed(W),
        };

        target = m_player.position + orient * g_tile_size;

        for ( u32 i = 0; i < target.s_size; i++ ) {
            if ( target[i] < 0 || target[i] >= g_world_size[i] * g_tile_size )
                orient[i] = 0;
        }

        movement(delta, orient, m_player);
        m_camera.target = m_player.position;

        for ( u32 i = 0; i < m_actors.length(); i++ ) {
            orient = {rand() % 3u - 1.f, rand() % 3u - 1.f};
            target = m_actors[i].position + orient * g_tile_size;

            for ( u32 i = 0; i < target.s_size; i++ ) {
                if ( target[i] < 0 || target[i] >= g_world_size[i] * g_tile_size )
                    orient[i] = 0;
            }

            movement(delta, orient, m_actors[i]);
        }
    }

    void
    after_step()
    {
        sf::RectangleShape rect;

        rect.setSize({g_tile_size, g_tile_size});

        Vec2u base = {
            (u32) max((i32) ceil((m_camera.target[0] - m_camera.offset[0]) / g_tile_size) - 1, 0),
            (u32) max((i32) ceil((m_camera.target[1] - m_camera.offset[1]) / g_tile_size) - 1, 0),
        };

        Vec2u stop = {
            min((i32) ceil((m_camera.target[0] + m_camera.offset[0]) / g_tile_size) + 1, (i32) g_world_size[0]),
            min((i32) ceil((m_camera.target[1] + m_camera.offset[1]) / g_tile_size) + 1, (i32) g_world_size[1]),
        };

        m_window.clear();

        for ( u32 i = base[1]; i < stop[1]; i++ ) {
            for ( u32 j = base[0]; j < stop[0]; j++ ) {
                rect.setFillColor(g_colors[m_world[{j, i}]]);
                rect.setPosition({
                    j * g_tile_size - m_camera.target[0] + m_camera.offset[0],
                    i * g_tile_size - m_camera.target[1] + m_camera.offset[1],
                });

                m_window.draw(rect);
            }
        }

        rect.setFillColor(sf::Color::Blue);
        rect.setPosition({
            m_player.position[0] - m_camera.target[0] + m_camera.offset[0],
            m_player.position[1] - m_camera.target[1] + m_camera.offset[1],
        });

        m_window.draw(rect);

        for ( u32 i = 0; i < m_actors.length(); i++ ) {
            rect.setFillColor(sf::Color::Cyan);
            rect.setPosition({
                m_actors[i].position[0] - m_camera.target[0] + m_camera.offset[0],
                m_actors[i].position[1] - m_camera.target[1] + m_camera.offset[1],
            });

            m_window.draw(rect);
        }

        m_window.display();
    }

private:
    sf::RenderWindow m_window;
    Array<Entity>    m_actors;
    Entity           m_player;
    Camera           m_camera;
    Array2D<u32>     m_world;
};

int
main(int, const char*[])
{
    Engine    engine;
    MainState state;

    engine.program("MainState", state);

    if ( engine.execute("MainState") )
        return 0;

    return 1;
}
