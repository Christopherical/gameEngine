#include <SFML/GpuPreference.hpp>

#include "Core/Engine.hpp"

SFML_DEFINE_DISCRETE_GPU_PREFERENCE

int main()
{
    Engine engine;

    while (engine.IsRunning())
    {
        engine.ProcessEvents();
        engine.Update();
        engine.Render();
    }
}