#include <utility>

#include "Core/EngineConfig.hpp"
#include "Graphics/Effects/EffectBloom.hpp"
#include "Graphics/Effects/EffectMonitor.hpp"
#include "Managers/RenderManager.hpp"
#include "Utils/Verify.hpp"

RenderManager::RenderManager() :
    target_(sf::Vector2u(gConfig.windowSize)),
    backgroundTexture_("Content/Textures/darkBackground.png"),
    background_(gConfig.windowSize)
{
    target_.setSmooth(true);

    background_.setTexture(&backgroundTexture_);
    background_.setFillColor(gConfig.backgroundColor);

    if (sf::Shader::isAvailable())
    {
        VERIFY(effectsTarget_.resize(sf::Vector2u(gConfig.windowSize)));

        effects_.emplace_back(std::make_unique<EffectBloom>());
        effects_.emplace_back(std::make_unique<EffectMonitor>());
    }
}


void RenderManager::Draw(const sf::Drawable& drawable)
{
    target_.draw(drawable);
}

void RenderManager::SetView(const sf::View& view)
{
    target_.setView(view);
}

void RenderManager::ResetView()
{
    SetView(target_.getDefaultView());
}

void RenderManager::BeginDrawing()
{
    target_.clear();
    Draw(background_);
}

const sf::Texture& RenderManager::FinishDrawing()
{
    target_.display();

    sf::RenderTexture* input = &target_;
    sf::RenderTexture* output = &effectsTarget_;

    for (const auto& effect : effects_)
    {

        output->clear();
        effect->Apply(input->getTexture(), *output);
        output->display();

        std::swap(input, output);
    }

    return input->getTexture();
}
