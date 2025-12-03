#include "Core/EngineVisitor.hpp"
#include "Core/Engine.hpp"


void EngineVisitor::operator()(const sf::Event::Closed&)
{
    engine.EventWindowClose();
}
void EngineVisitor::operator()(const sf::Event::Resized& resized)
{
    engine.EventWindowResized(resized.size);
}

void EngineVisitor::operator()(const sf::Event::FocusLost&)
{
    engine.EventWindowFocusLost();
}

void EngineVisitor::operator()(const sf::Event::FocusGained&)
{
    engine.EventWindowFocusGained();
}

void EngineVisitor::operator()(const sf::Event::JoystickConnected&) {}

void EngineVisitor::operator()(const sf::Event::JoystickDisconnected&) {}

void EngineVisitor::operator()(const sf::Event::KeyPressed&) {}

void EngineVisitor::operator()(const sf::Event::JoystickButtonPressed&) {}
