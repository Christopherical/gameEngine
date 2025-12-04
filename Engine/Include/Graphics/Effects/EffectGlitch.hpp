#pragma once

#include "Graphics/Effect.hpp"

#include <SFML/Graphics/Shader.hpp>
#include <SFML/System/Clock.hpp>

class EffectGlitch : public Effect
{
private:
    sf::Shader shader_;
    sf::Clock clock_;

public:
    EffectGlitch();

    void Apply(const sf::Texture& input, sf::RenderTarget& output) override;
};