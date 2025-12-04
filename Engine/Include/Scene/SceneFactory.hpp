#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Core/EngineContext.hpp"
#include "Scene/Scene.hpp"

namespace SceneFactory
{
    using Scenes = std::unordered_map<std::string, std::unique_ptr<Scene>>;

    Scenes CreateScenes(EngineContext& context);
} // namespace SceneFactory
