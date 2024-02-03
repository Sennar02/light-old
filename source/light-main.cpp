#include <light/Engine/import.hpp>
#include <stdio.h>

using namespace lgh;

static const u32   g_tile_size   = 48u;        // pixels.
static const Vec2u g_window_size = {32u, 18u}; // tiles.
static const Vec2u g_camera_size = {9u, 9u};   // tiles.
static const Vec2u g_world_size  = {16u, 16u}; // tiles.

static const u32   g_tile_half   = g_tile_size / 2u;   // pixels.
static const Vec2u g_window_half = g_window_size / 2u; // tiles.
static const Vec2u g_camera_half = g_camera_size / 2u; // tiles.

static const u32 g_world_area = g_world_size[0] * g_world_size[1];

static const u32 g_colors_size = 3u;

static const sf::Color g_colors[g_colors_size] = {
    {255u,    0,   0},
    {255u, 255u,   0},
    {255u,  96u, 32u},
};

static bool g_auto_play = false;

struct Camera
{
    Vec2f follow;
    Vec2f offset;

    Vec2f
    origin() const
    {
        return follow - offset;
    }

    Vec2f
    finish() const
    {
        return follow + offset;
    }
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

static void
move(f32 delta, Vec2f orient, Movement& self)
{
    Vec2f distance;
    Vec2f movement;

    if ( self.moving ) {
        movement = self.orient * self.speed * delta;
        distance = self.target - self.position;

        for ( u32 i = 0; i < movement.s_size; i++ ) {
            if ( abs(movement[i]) > abs(distance[i]) )
                self.position[i] = self.target[i];
            else
                self.position[i] += movement[i];
        }

        if ( self.position == self.target )
            self.moving = false;
    } else {
        if ( orient != Vec2u {} ) {
            self.target = self.position + (orient * g_tile_size);
            self.speed  = self.speed_max / orient.strength();
            self.orient = orient;
            self.moving = true;
        }
    }
}

struct Drawable
    : public Movement
{
    sf::Color color;
};

void
draw(sf::RectangleShape& rect, sf::RenderTarget& render, const Camera& camera, const Drawable& self)
{
    Vec2f origin = camera.origin();
    Vec2u offset = (g_window_half - g_camera_half) * g_tile_size;

    rect.setFillColor(self.color);
    rect.setPosition({
        self.position[0] - origin[0] + offset[0],
        self.position[1] - origin[1] + offset[1],
    });

    render.draw(rect);
}

void
draw(sf::RectangleShape& rect, sf::RenderTarget& render, const Camera& camera, const Array2D<u32>& world)
{
    Vec2f origin = camera.origin();
    Vec2f finish = camera.finish();
    Vec2u offset = (g_window_half - g_camera_half) * g_tile_size;
    u32   tile;

    Vec4u bounds = {
        max(floor(origin[0] / g_tile_size) - 1.f, 0),
        min(ceil(finish[0] / g_tile_size) + 1.f, g_world_size[0]),
        max(floor(origin[1] / g_tile_size) - 1.f, 0),
        min(ceil(finish[1] / g_tile_size) + 1.f, g_world_size[1]),
    };

    for ( u32 i = bounds[2]; i < bounds[3]; i++ ) {
        for ( u32 j = bounds[0]; j < bounds[1]; j++ ) {
            tile = world[Vec2u {j, i}];

            rect.setFillColor(g_colors[tile]);
            rect.setPosition({
                j * g_tile_size - origin[0] + offset[0],
                i * g_tile_size - origin[1] + offset[1],
            });

            render.draw(rect);
        }
    }
}

struct Entity
    : public Drawable
{ };

class MainState
    : public State
{
public:
    MainState()
        : m_window {}
        , m_rect {}
        , m_player {0}
        , m_camera {}
        , m_actors {g_origin, 10u}
        , m_world {g_origin, g_world_area, g_world_size[0]}
    {
        m_rect.setSize({g_tile_size, g_tile_size});
    }

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

        m_actors[m_player].speed_max = 10.f * g_tile_size;
        m_actors[m_player].color     = sf::Color::White;

        for ( u32 i = 0; i < m_actors.length(); i++ ) {
            m_actors[i].position = {
                rand() % g_world_size[0] * g_tile_size,
                rand() % g_world_size[1] * g_tile_size,
            };

            if ( m_player == i && g_auto_play == false ) continue;

            m_actors[i].speed_max = (rand() % 6u + 2u) * g_tile_size;
            m_actors[i].color     = sf::Color {
                (u8) (rand() % 256u),
                (u8) (rand() % 256u),
                (u8) (rand() % 256u),
            };
        }

        m_camera.follow = m_actors[m_player].position + g_tile_half;
        m_camera.offset = g_camera_half * g_tile_size;
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

        target = m_actors[m_player].position + orient * g_tile_size;

        for ( u32 i = 0; i < target.s_size; i++ ) {
            if ( target[i] < 0 || target[i] >= g_world_size[i] * g_tile_size )
                orient[i] = 0;
        }

        move(delta, orient, m_actors[m_player]);
        m_camera.follow = m_actors[m_player].position + g_tile_half;

        for ( u32 i = 0; i < m_actors.length(); i++ ) {
            orient = m_actors[i].orient;

            if ( m_player == i && g_auto_play == false ) continue;

            if ( rand() % 10 == 0 )
                orient = {rand() % 3u - 1.f, rand() % 3u - 1.f};

            target = m_actors[i].position + orient * g_tile_size;

            for ( u32 i = 0; i < target.s_size; i++ ) {
                if ( target[i] < 0 || target[i] >= g_world_size[i] * g_tile_size )
                    orient[i] = 0;
            }

            move(delta, orient, m_actors[i]);
        }
    }

    void
    after_step()
    {
        m_window.clear();

        draw(m_rect, m_window, m_camera, m_world);

        for ( u32 i = 0; i < m_actors.length(); i++ )
            draw(m_rect, m_window, m_camera, m_actors[i]);

        m_window.display();
    }

private:
    sf::RenderWindow   m_window;
    sf::RectangleShape m_rect;
    u32                m_player;
    Camera             m_camera;
    Array<Entity>      m_actors;
    Array2D<u32>       m_world;
};

int
main(int argc, const char* argv[])
{
    Engine    engine;
    MainState state;

    srand(time(0));

    if ( argc == 2 && strncmp(argv[1], "--autoplay", 11u) == 0 )
        g_auto_play = true;

    engine.program("MainState", state);

    if ( engine.execute("MainState") )
        return 0;

    return 1;
}



// #include <light/Engine/import.hpp>

// namespace lgh
// {
//     using Color    = Vector3D<u8>;
//     using Position = Vec2f;

//     struct Velocity
//     {
//         f32 value;
//         f32 limit;
//     };

//     struct Movement
//     {
//         Vec2f destin;
//         Vec2f orient;
//         bool  moving;
//     };

//     struct MovementSystem
//     {
//         static const u32 s_unit = 1u;

//         static void
//         udpate(Movement& movement, Velocity& velocity, Position& position, Vec2f orient, f32 step)
//         {
//             Vec2f dist;
//             Vec2f incr;

//             if ( movement.moving == false ) {
//                 if ( orient != Vec2u {} ) {
//                     velocity.value = velocity.limit / orient.strength();

//                     movement.destin = position + (orient * s_unit);
//                     movement.orient = orient;
//                     movement.moving = true;
//                 }
//             } else {
//                 incr = movement.orient * velocity.value * step;
//                 dist = movement.destin - position;

//                 for ( u32 i = 0; i < position.s_size; i++ ) {
//                     position[i] += incr[i];

//                     if ( abs(dist[i]) < abs(incr[i]) )
//                         position[i] = movement.destin[i];
//                 }

//                 if ( position == movement.destin )
//                     movement.moving = false;
//             }
//         }
//     };

//     struct DrawingSystem
//     {
//         static void
//         update(Position& position, Color& color, sf::RenderTarget& render)
//         {
//             sf::RectangleShape
//         }
//     };
// } // namespace lgh
