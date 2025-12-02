#include "Core/Engine.hpp"
#include "Core/EngineVisitor.hpp"

void EngineVisitor::operator()(const sf::Event::Closed&) {
    engine.EventWindowClose();
}