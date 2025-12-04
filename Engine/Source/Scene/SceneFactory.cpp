#include "Scene/SceneFactory.hpp"

#include "Bounce.hpp"

namespace SceneFactory
{
    Scenes CreateScenes(EngineContext& context)
    {
        Scenes scenes;

        scenes.emplace("Bounce", std::make_unique<Bounce::Game>(context));

        return scenes;
    }
} // namespace SceneFactory