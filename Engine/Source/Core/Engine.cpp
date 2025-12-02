#include "Core/Engine.hpp"
#include "Engine.hpp"

Engine::Engine() :
    window_(sf::VideoMode({800, 600}), "Engine Window")
{
    window_.setIcon(sf::Image("Content/Textures/crystalball.png"));
    window_.setMinimumSize(window_.getSize() / 2u);
}

bool Engine::IsRunning() const
{
    return window_.isOpen();
}

void Engine::ProcessEvents()
{
    while (const std::optional<sf::Event> event = window_.pollEvent())
    {
        event->visit(EngineVisitor{*this});
    }
}

void Engine::Update()
{
}

void Engine::Render()
{
    window_.clear();
    window_.display();
}

void Engine::EventWindowClose()
{
    window_.close();
}
