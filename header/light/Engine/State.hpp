#ifndef LIGHT_ENGINE_STATE_HPP
#define LIGHT_ENGINE_STATE_HPP

#include <light/Engine/define.hpp>

namespace lgh
{
    class State
    {
    public:
        /**
         *
         */
        State();

        /**
         *
         */
        virtual ~State() = default;

        /**
         * Called once when programming
         * the state machine.
         */
        virtual bool
        attach();

        /**
         * Called once when the engine starts.
         */
        virtual void
        start();

        /**
         * Called once when the engine cleans.
         */
        virtual void
        clean();

        /**
         * Called on every entering transition.
         */
        virtual void
        enter();

        /**
         * Called on every leaving transition.
         */
        virtual void
        leave();

        /**
         * Called always once every frame, before fixed_step.
         */
        virtual bool
        input();

        /**
         * Called from zero tu multiple times every frame.
         */
        virtual void
        fixed_step(f32 delta);

        /**
         * Called always once every frame, after fixed_step.
         */
        virtual void
        after_step();

    public:
        /**
         * Name of the next state.
         */
        String next;
    };
} // namespace lgh

#endif // LIGHT_ENGINE_STATE_HPP
