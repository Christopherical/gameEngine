#pragma once

#include <SFML/Graphics.hpp>

#include "Core/EngineVisitor.hpp"

class Engine
{
private:
    sf::RenderWindow window_;

public:
    Engine();

    bool IsRunning() const;

    void ProcessEvents();
    void Update();
    void Render();

private:
    friend EngineVisitor;

    void EventWindowClose();
};