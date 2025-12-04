#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

class Effect{
    private:
    public:
    virtual ~Effect() = default;

    virtual void Apply(const sf::Texture& source, sf::RenderTarget& target) = 0;
};