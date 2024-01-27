#include <light/Engine/StateMachine.hpp>

namespace lgh
{
    StateMachine::StateMachine()
        : m_table {g_origin, 256u}
        , m_stack {g_origin, 256u}
    { }

    Result<bool, fail::Insert>
    StateMachine::insert(const String& name, State& state)
    {
        if ( name == "" ) return fail::InvalidElement;

        if ( state.attach() )
            return m_table.insert(name, &state);

        return fail::InvalidElement;
    }

    State*
    StateMachine::launch(const String& name)
    {
        State* state = peek();

        if ( state != 0 ) state->leave();

        if ( change(name) ) {
            state = peek();

            if ( state != 0 )
                state->enter();
        } else
            state = 0;

        return state;
    }

    HashTable<String, State*>&
    StateMachine::table()
    {
        return m_table;
    }

    ArrayDeque<State*>&
    StateMachine::stack()
    {
        return m_stack;
    }

    State*
    StateMachine::peek() const
    {
        u32 index = m_stack.count() - 1u;

        return m_stack.find(index, 0);
    }

    bool
    StateMachine::change(const String& name)
    {
        State* state = m_table.find(name, 0);

        if ( state != 0 )
            return m_stack.insert(state).is_item();

        return m_stack.remove(algo::Tail).is_item();
    }
} // namespace lgh
