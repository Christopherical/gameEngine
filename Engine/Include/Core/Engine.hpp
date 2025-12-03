#pragma once

#include <SFML/Graphics.hpp>

#include "Core/EngineContext.hpp"
#include "Core/EngineVisitor.hpp"

class Engine
{
private:
    sf::RenderWindow window_;
    EngineContent context_;

public:
    Engine();

    bool IsRunning() const;

    void ProcessEvents();
    void Update();
    void Render();

private:
    friend EngineVisitor;

    void EventWindowClose();
    void EventWindowResized(sf::Vector2u size);
    void EventWindowFocusLost();
    void EventWindowFocusGained();
};