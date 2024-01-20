#include <light/Engine/System.hpp>

namespace lgt
{
    System::System()
        : m_actors {0}
    { }

    void
    System::enter()
    { }

    void
    System::leave()
    { }

    void
    System::fixed_step(f32)
    { }

    void
    System::after_step()
    { }
} // namespace lgt
