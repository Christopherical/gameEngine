#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Core/EngineContext.hpp"
#include "Scene/Scene.hpp"

namespace SceneFactory
{
    std::unordered_map<std::string, std::unique_ptr<Scene>> CreateScenes(EngineContext& context);
} // namespace SceneFactory
