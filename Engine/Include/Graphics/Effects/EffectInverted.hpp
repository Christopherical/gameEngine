#pragma once

#include "Graphics/Effect.hpp"

#include <SFML/Graphics/Shader.hpp>

class EffectInverted : public Effect
{
private:
    sf::Shader shader_;

public:
    EffectInverted();

    void Apply(const sf::Texture& source, sf::RenderTarget& target) override;
};