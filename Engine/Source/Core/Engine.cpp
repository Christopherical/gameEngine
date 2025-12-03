#include "Core/Engine.hpp"
#include "Core/EngineConfig.hpp"
#include "Core/EngineVisitor.hpp"
#include "Utils/Log.hpp"

Engine::Engine() :
    window_(sf::VideoMode(sf::Vector2u(gConfig.windowSize)), gConfig.windowTitle)
{
    window_.setIcon(sf::Image("Content/Textures/crystalball.png"));
    window_.setMinimumSize(window_.getSize() / 2u);

    if (gConfig.disableSfmlLogs)
    {
        sf::err().rdbuf(nullptr);
    }

    LOG_INFO("Window Created");
}

bool Engine::IsRunning() const
{
    return window_.isOpen();
}

void Engine::ProcessEvents()
{
    while (const std::optional<sf::Event> event = window_.pollEvent())
    {
        event->visit(EngineVisitor {*this});
    }
}

void Engine::Update() {}

void Engine::Render()
{
    window_.clear();
    window_.display();
}

void Engine::EventWindowClose()
{
    window_.close();
    LOG_INFO("Window Closed");
}

void Engine::EventWindowResized(sf::Vector2u size)
{
    LOG_INFO("Window resized to {}x{}", size.x, size.y);
}

void Engine::EventWindowFocusLost()
{
    LOG_INFO("Window focus lost");
}

void Engine::EventWindowFocusGained()
{
    LOG_INFO("Window focus gained");
}
