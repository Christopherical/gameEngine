#include "Scene/SceneFactory.hpp"

#include "Bounce.hpp"
#include "Clicker.hpp"

namespace SceneFactory
{
    std::unordered_map<std::string, std::unique_ptr<Scene>> CreateScenes(EngineContext& context)
    {
        std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;

        scenes.emplace("Bounce", std::make_unique<Bounce::Game>(context));
        scenes.emplace("Clicker", std::make_unique<Clicker::Game>(context));
        return scenes;
    }
} // namespace SceneFactory