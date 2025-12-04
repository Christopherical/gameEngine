#include "Graphics/Effects/EffectMonitor.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include "Utils/Verify.hpp"

EffectMonitor::EffectMonitor() {
    VERIFY(shader_.loadFromFile("Content/Shaders/Monitor.frag", sf::Shader::Type::Fragment));
}

void EffectMonitor::Apply(const sf::Texture& input, sf::RenderTarget& output) {
    shader_.setUniform("sourceTexture", sf::Shader::CurrentTexture);
    shader_.setUniform("resolution", sf::Vector2f(input.getSize()));
    shader_.setUniform("time", clock_.getElapsedTime().asSeconds());

    output.draw(sf::Sprite(input), &shader_);
}
