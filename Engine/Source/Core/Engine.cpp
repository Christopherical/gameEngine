#include "Core/Engine.hpp"
#include "Core/EngineConfig.hpp"
#include "Utils/Log.hpp"

Engine::Engine() :
    window_(sf::VideoMode(sf::Vector2u(gConfig.windowSize)), gConfig.windowTitle),
    context_(window_),
    scenes_(SceneFactory::CreateScenes(context_)),
    currentScene_(nullptr)
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
    if (const auto nextScene = context_.scenes.FetchNextChange())
    {
        EventSceneChange(*nextScene);
    }

    while (const std::optional<sf::Event> event = window_.pollEvent())
    {
        event->visit(EngineVisitor {*this});
        context_.gui.ProcessEvent(*event);

        // currentScene_->OnEvent(*event);
    }
}

void Engine::Update()
{
    context_.time.Update();
    context_.cursor.Update(context_.time.GetDeltaTime());

    // currentScene_->Update();
}

void Engine::Render()
{
    window_.clear();
    context_.renderer.BeginDrawing();
    // currentScene_->Render();
    window_.draw(sf::Sprite(context_.renderer.FinishDrawing()));

    context_.gui.Render();
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
    currentScene_->OnPause(true);
    LOG_INFO("Window focus lost");
}

void Engine::EventWindowFocusGained()
{
    currentScene_->OnPause(false);
    LOG_INFO("Window focus gained");
}

void Engine::EventWindowScreenshot() const
{
    context_.screenshot.Take();
}

void Engine::EventGamepadConnected(int id)
{
    LOG_INFO("Gamepad {} connected", id);
}

void Engine::EventGamepadDisconnected(int id)
{
    LOG_INFO("Gamepad {} disconnected", id);
}
void Engine::EventSceneChange(const std::string& name)
{
    assert(scenes_.contains(name));
    Scene* newScene = scenes_.at(name).get();

    if (currentScene_)
    {
        currentScene_->OnCleanup();
    }
    context_.input.Clear();

    // currentScene_ = newScene;
    // currentScene_->Start();
}
void Engine::EventSceneRestart()
{
    context_.scenes.RestartCurrentScene();
}
void Engine::EventSceneMenuReturn()
{
    context_.scenes.ChangeScene("Menu");
}