#ifndef LIGHT_ENGINE_SYSTEM_HPP
#define LIGHT_ENGINE_SYSTEM_HPP

#include <light/Engine/define.hpp>

namespace lgt
{
    class System
    {
    public:
        /**
         *
         */
        System();

        /**
         *
         */
        virtual ~System() = default;

        /**
         *
         */
        virtual bool
        accept(void* actors) = 0;

        /**
         *
         */
        virtual void
        enter();

        /**
         *
         */
        virtual void
        leave();

        /**
         *
         */
        virtual void
        fixed_step(f32 delta);

        /**
         *
         */
        virtual void
        after_step();

    protected:
        /**
         *
         */
        void* m_actors;
    };
} // namespace lgt

#endif // LIGHT_ENGINE_SYSTEM_HPP
