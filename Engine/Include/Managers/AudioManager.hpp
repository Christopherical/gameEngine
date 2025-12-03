#pragma once

#include <SFML/System/Vector3.hpp>

class AudioManager
{
    public:
    void SetGlobalVolume(float volume);
    float GetGlobalVolume() const;

    void SetListenerPosition(const sf::Vector3f& position);
    sf::Vector3f GetListenerPosition() const;

    void SetListenerDirection(const sf::Vector3f& direction);
    sf::Vector3f GetListenerDirection() const;

};