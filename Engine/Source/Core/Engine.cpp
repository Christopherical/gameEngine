#include "Core/Engine.hpp"
#include "Core/EngineConfig.hpp"
#include "Utils/Log.hpp"

Engine::Engine() :
    window_(sf::VideoMode(sf::Vector2u(gConfig.windowSize)), gConfig.windowTitle), context_(window_)
{
    window_.setIcon(sf::Image("Content/Textures/crystalball.png"));
    window_.setMinimumSize(window_.getSize() / 2u);
    window_.setKeyRepeatEnabled(false);
    window_.setMouseCursorVisible(false);

    if (gConfig.disableSfmlLogs)
    {
        sf::err().rdbuf(nullptr);
    }

    context_.audio.SetGlobalVolume(gConfig.globalVolume);

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

void Engine::Update()
{
    context_.time.Update();
    context_.cursor.Update(context_.time.GetDeltaTime());
}

void Engine::Render()
{
    window_.clear();
    context_.renderer.BeginDrawing();
    window_.draw(sf::Sprite(context_.renderer.FinishDrawing()));

    context_.cursor.Render();

    window_.display();
}

void Engine::EventWindowClose()
{
    window_.close();
    LOG_INFO("Window closed");
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

void Engine::EventWindowScreenshot() const {
    context_.screenshot.Take();
}

void Engine::EventGamepadConnected(int id) {
    LOG_INFO("Gamepad {} connected", id);
}

void Engine::EventGamepadDisconnected(int id) {
    LOG_INFO("Gamepad {} disconnected", id);
}
