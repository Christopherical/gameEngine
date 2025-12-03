#include "Managers/TimeManager.hpp"

#include "Core/EngineConfig.hpp"

float TimeManager::GetDeltaTime() const
{
    return deltaTime_.asSeconds();
}

float TimeManager::GetElapsedTime() const
{
    return clock_.getElapsedTime().asSeconds();
}

void TimeManager::Update()
{
    const sf::Time currentTime = clock_.getElapsedTime();
    deltaTime_ = currentTime - previousTime_;
    if (deltaTime_ > gConfig.maximumDeltaTime)
    {
        deltaTime_ = gConfig.maximumDeltaTime;
    }

    previousTime_ = currentTime;
}