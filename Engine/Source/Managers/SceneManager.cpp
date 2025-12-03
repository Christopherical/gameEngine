#include "Managers/SceneManager.hpp"

#include "Utils/Log.hpp"
#include <utility>

std::optional<std::string> SceneManager::FetchNextChange()
{
    if (nextScene_)
    {
        if (currentScene_ == *nextScene_)
        {
            LOG_INFO("Restarting scene: {}", currentScene_);
        }
        else
        {
            LOG_INFO("Changing scene to: {}", *nextScene_);
        }

        currentScene_ = *nextScene_;

        // std::exchange - Give what's in nextScene_ and then reset it to nullopt
        return std::exchange(nextScene_, std::nullopt);
    }
    return std::nullopt;
}

void SceneManager::ChangeScene(std::string_view name)
{
    if(!nextScene_){
        nextScene_ = name;
    }
}

void SceneManager::RestartCurrentScene()
{
    ChangeScene(currentScene_);
}