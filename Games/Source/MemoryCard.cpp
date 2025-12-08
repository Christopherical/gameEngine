#include "MemoryCard.hpp"

using namespace MemoryCard;

Game::Game(EngineContext& context) : Scene(context)
{
    InitCardPair();
}

void Game::InitCardPair()
{
    cardPair_.visibleCooldown.SetDuration(CARD_PAIR_VISIBLE_COOLDOWN_DURATION);
}

void Game::Start()
{
    StartStats();
    StartCards();
}

void Game::StartStats()
{
    stats_.level = 0;
}

void Game::StartCards()
{
    EventCardsSpawn();
}

void Game::OnEvent(const sf::Event& event)
{
    if (event.is<sf::Event::MouseButtonPressed>() || event.is<sf::Event::JoystickButtonPressed>())
    {
        if (!IsCardPairSelected())
        {
            EventCardClicked();
        }
    }
}

void Game::EventCardClicked()
{
    for (auto& card : cards_)
    {
        if (!card.flipped && IsCardHovered(card))
        {
            EventCardFlip(card);
            break;
        }
    }
}

void Game::EventCardFlip(Card& card)
{
    card.shape.setFillColor(card.color);
    card.flipped = true;
    if (!cardPair_.first)
    {
        cardPair_.first = &card;
    }
    else
    {
        cardPair_.second = &card;
        cardPair_.visibleCooldown.Restart();
    }
}

void MemoryCard::Game::EventCardPairEvaluate()
{
    if (cardPair_.first->color == cardPair_.second->color)
    {
        cardPair_.first->found = true;
        cardPair_.second->found = true;
    }
    else
    {
        cardPair_.first->shape.setFillColor(sf::Color::Transparent);
        cardPair_.second->shape.setFillColor(sf::Color::Transparent);

        cardPair_.first->flipped = false;
        cardPair_.second->flipped = false;
    }
    EventCardPairReset();
}

void Game::EventCardsSpawn()
{
    std::vector<sf::Color> colors = GenerateCardColors();
    int count = (int)colors.size();

    int rows = (int)std::sqrt(count);
    int cols = (count + rows - 1) / rows;

    cards_.clear();
    cards_.reserve(count);

    for (int i = 0; i < count; ++i)
    {
        sf::Vector2f size = gConfig.windowSize.componentWiseDiv({(float)cols, (float)rows});
        sf::Vector2f position(size.x * (i % cols), size.y * (i / cols));

        EventCardsSpawn({position, size}, colors[i]);
    }

    EventCardPairReset();
}

void Game::EventCardPairReset()
{
    cardPair_.first = nullptr;
    cardPair_.second = nullptr;
}

void Game::EventCardsSpawn(sf::FloatRect bounds, sf::Color color)
{
    auto& card = cards_.emplace_back();

    card.shape.setTexture(ctx.resources.FetchTexture(CARD_TEXTURE_FILENAME));
    card.shape.setFillColor(sf::Color::Transparent);
    card.shape.setOutlineColor(CARD_OUTLINE_COLOR);
    card.shape.setOutlineThickness(-1);
    card.shape.setSize(bounds.size);
    card.shape.setPosition(bounds.position);

    card.color = color;
    card.flipped = false;
    card.found = false;
}

std::vector<sf::Color> Game::GenerateCardColors() const
{
    std::vector<sf::Color> colors;

    int count = CARDS_COUNT_INITIAL + stats_.level * CARDS_COUNT_PER_LEVEL;

    colors.reserve(count);

    for (int i = 0; i < count / 2; ++i)
    {
        sf::Color color = CARDS_COLORS[i % CARDS_COLORS.size()];
        colors.emplace_back(color);
        colors.emplace_back(color);
    }

    std::ranges::shuffle(colors, std::default_random_engine(std::random_device {}()));
    return colors;
}


void Game::Update()
{
    if (IsCardPairSelected() && cardPair_.visibleCooldown.IsOver())
    {
        EventCardPairEvaluate();

        if (std::ranges::all_of(cards_, [](const Card& card) { return card.found; }))
        {
            stats_.level++;
            EventCardsSpawn();
        }
    }
}

bool Game::IsCardHovered(const Card& card) const
{
    return Contains(card.shape, ctx.cursor.GetPosition());
}

bool Game::IsCardPairSelected() const
{
    return cardPair_.first && cardPair_.second;
}
void Game::Render() const
{
    for (const auto& card : cards_)
    {
        ctx.renderer.Draw(card.shape);
    }
}

void Game::OnPause(bool paused)
{
    if (paused)
    {
        cardPair_.visibleCooldown.Stop();
    }
    else
    {
        cardPair_.visibleCooldown.Start();
    }
}