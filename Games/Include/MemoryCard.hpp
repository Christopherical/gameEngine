#pragma once

#include "Types/MemoryCardTypes.hpp "

namespace MemoryCard
{
    class Game : public Scene
    {
    private:
        std::vector<Card> cards_;
        CardPair cardPair_;
        Stats stats_;

    public:
        Game(EngineContext& context);

        void Start();
        void OnEvent(const sf::Event&);
        void Update();
        void Render() const;
        void OnPause(bool);

    private:
        void InitCardPair();

        void StartStats();
        void StartCards();

        void EventCardsSpawn();
        void EventCardsSpawn(sf::FloatRect bounds, sf::Color color);
        void EventCardClicked();
        void EventCardFlip(Card& card);
        void EventCardPairEvaluate();
        void EventCardPairReset();

        std::vector<sf::Color> GenerateCardColors() const;
        bool IsCardHovered(const Card& card) const;
        bool IsCardPairSelected() const;
    };
} // namespace MemoryCard