#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include "Graphics/Effects/EffectGlitch.hpp"
#include "Utils/Verify.hpp"



EffectGlitch::EffectGlitch() {
    VERIFY(shader_.loadFromFile("Content/Shaders/Glitch.frag", sf::Shader::Type::Fragment));
}

void EffectGlitch::Apply(const sf::Texture& input, sf::RenderTarget& output) {
    shader_.setUniform("sourceTexture", sf::Shader::CurrentTexture);
    shader_.setUniform("time", clock_.getElapsedTime().asSeconds());

    output.draw(sf::Sprite(input), &shader_);
}
