#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Managers/RandomManager.hpp"
#include "Managers/TimeManager.hpp"
#include "Managers/SaveManager.hpp"
#include "Managers/ClipboardManager.hpp"
#include "Managers/ResourceManager.hpp"
#include "Managers/AudioManager.hpp"
#include "Managers/InputManager.hpp"
#include "Managers/RenderManager.hpp"
#include "Managers/ScreenshotManager.hpp"
#include "Managers/CursorManager.hpp"

struct EngineContext
{
    RandomManager random;
    TimeManager time;
    SaveManager save;
    ClipboardManager clipboard;
    ResourceManager resources;
    AudioManager audio;
    InputManager input;
    RenderManager renderer;
    ScreenshotManager screenshot;
    CursorManager cursor;

    EngineContext(sf::RenderWindow& window) :
        screenshot(window),
        cursor(window)
    {}


};