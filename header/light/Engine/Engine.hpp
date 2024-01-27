#ifndef LIGHT_ENGINE_ENGINE_HPP
#define LIGHT_ENGINE_ENGINE_HPP

#include <light/Engine/define.hpp>
#include <light/Engine/State.hpp>
#include <light/Engine/StateMachine.hpp>

namespace lgh
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
        program(const String& name, State& state);

        /**
         *
         */
        bool
        execute(const String& name, u32 frames = 80u);

    private:
        /**
         *
         */
        State*
        start(const String& name);

        /**
         *
         */
        void
        clean();

        /**
         *
         */
        State*
        input();

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
        StateMachine m_machine;

        /**
         *
         */
        State* m_state;
    };
} // namespace lgh

#endif // LIGHT_ENGINE_ENGINE_HPP
