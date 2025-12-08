#include <SFML/GpuPreference.hpp>
#include <SFML/System/Sleep.hpp>

#include "Core/Engine.hpp"

SFML_DEFINE_DISCRETE_GPU_PREFERENCE

int main()
{
    Engine engine; // Initializes everything.

    while (engine.IsRunning())
    {
        engine.ProcessEvents(); // Handles events like input, window, etc.

        if (!engine.HasFocus()) // Pause when the window is not focused.
        {
            sf::sleep(sf::milliseconds(10));
            continue;
        }

        engine.Update(); // Updates game logic.
        engine.Render(); // Renders the current frame.
    }
}