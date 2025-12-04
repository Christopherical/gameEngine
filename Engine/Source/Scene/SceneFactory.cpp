#include "Scene/SceneFactory.hpp"

namespace SceneFactory
{
    Scenes CreateScenes(EngineContext& context)
    {
        Scenes scenes;

        // Example of adding scenes:
        // scenes["MainMenu"] = std::make_unique<MainMenuScene>(context);
        // scenes["GameLevel"] = std::make_unique<GameLevelScene>(context);

        return scenes;
    }
} // namespace SceneFactory