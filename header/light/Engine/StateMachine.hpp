#ifndef LIGHT_ENGINE_STATE_MACHINE_HPP
#define LIGHT_ENGINE_STATE_MACHINE_HPP

#include <light/Engine/define.hpp>
#include <light/Engine/State.hpp>

namespace lgh
{
    class StateMachine
    {
    public:
        StateMachine();

        Result<bool, fail::Insert>
        insert(const String& name, State& state);

        State*
        launch(const String& name);

        HashTable<String, State*>&
        table();

        ArrayDeque<State*>&
        stack();

    private:
        State*
        peek() const;

        bool
        change(const String& name);

    private:
        HashTable<String, State*> m_table;
        ArrayDeque<State*>        m_stack;
    };
} // namespace lgh

#endif // LIGHT_ENGINE_STATE_MACHINE_HPP
