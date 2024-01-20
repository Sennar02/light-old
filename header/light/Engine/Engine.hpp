#ifndef LIGHT_ENGINE_ENGINE_HPP
#define LIGHT_ENGINE_ENGINE_HPP

#include <light/Engine/define.hpp>
#include <light/Engine/System.hpp>

namespace lgt
{
    class Engine
    {
    public:
        /**
         *
         */
        Engine();

        /**
         *
         */
        Result<bool, fail::Insert>
        insert(System& system);

        /**
         *
         */
        bool
        loop(u32 frames = 64u);

    private:
        /**
         *
         */
        void
        enter();

        /**
         *
         */
        void
        leave();

        /**
         *
         */
        void
        fixed_step(f32 delta);

        /**
         *
         */
        void
        after_step();

    private:
        /**
         *
         */
        ArrayDeque<System*> m_queue;
    };
} // namespace lgt

#endif // LIGHT_ENGINE_ENGINE_HPP
