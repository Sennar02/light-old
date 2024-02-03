#include <light/Engine/import.hpp>

namespace lgh
{
    using Color    = Vector3D<u8>;
    using Position = Vec2f;

    struct Velocity
    {
        f32 value;
        f32 limit;
    };

    struct Movement
    {
        Vec2f destin;
        Vec2f orient;
        bool  moving;
    };

    struct MovementSystem
    {
        static const u32 s_unit = 1u;

        static void
        udpate(Movement& movement, Velocity& velocity, Position& position, Vec2f orient, f32 step)
        {
            Vec2f dist;
            Vec2f incr;

            if ( movement.moving == false ) {
                if ( orient != Vec2u {} ) {
                    velocity.value = velocity.limit / orient.strength();

                    movement.destin = position + (orient * s_unit);
                    movement.orient = orient;
                    movement.moving = true;
                }
            } else {
                incr = movement.orient * velocity.value * step;
                dist = movement.destin - position;

                for ( u32 i = 0; i < position.s_size; i++ ) {
                    position[i] += incr[i];

                    if ( abs(dist[i]) < abs(incr[i]) )
                        position[i] = movement.destin[i];
                }

                if ( position == movement.destin )
                    movement.moving = false;
            }
        }
    };

    struct DrawingSystem
    {
        static void
        update(Position& position, Color& color, sf::RenderTarget& render)
        {
            sf::RectangleShape
        }
    };
} // namespace lgh
