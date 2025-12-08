#include "Clicker.hpp"

using namespace Clicker;

//
Game::Game(EngineContext& context) : Scene(context)
{
    InitTarget();
    InitStats();
}

void Game::InitTarget()
{
    target_.shape.setTexture(ctx.resources.FetchTexture(TARGET_TEXTURE_FILENAME));
    target_.shape.setRadius(TARGET_RADIUS);
    target_.shape.setOrigin(target_.shape.getGeometricCenter());

    target_.teleportCooldown.SetDuration(TARGET_TELEPORT_COOLDOWN_DURATION);
}

void Game::InitStats()
{
    stats_.scoreText.setFillColor(STATS_SCORE_TEXT_COLOR);
    stats_.scoreText.setCharacterSize(STATS_TEXT_SIZE);
    stats_.scoreText.setPosition({5, 5});

    stats_.finalCooldown.SetDuration(STATS_FINAL_COOLDOWN_DURATION);

    stats_.finalCooldownText.setFillColor(STATS_FINAL_COOLDOWN_TEXT_COLOR);
    stats_.finalCooldownText.setCharacterSize(STATS_TEXT_SIZE);
    stats_.finalCooldownText.setPosition({5, 50});

    stats_.bestTimeText.setFillColor(STATS_BEST_TIME_TEXT_COLOR);
    stats_.bestTimeText.setCharacterSize(STATS_TEXT_SIZE);
    stats_.bestTimeText.setPosition({5, 95});
}

void Game::Start()
{
    ctx.cursor.SetSpeed(CURSOR_SPEED);

    BindInputs();

    StartTarget();
    StartStats();
}

void Game::BindInputs()
{
    ctx.input.Bind(Click, Input::Mouse {sf::Mouse::Button::Left});
    ctx.input.Bind(Click, Input::Gamepad {GamepadButton::South});
}

void Game::StartTarget()
{
    target_.shape.setFillColor(TARGET_COLOR);
    target_.shape.setPosition(gConfig.windowSize / 2.f);
}

void Game::StartStats()
{
    stats_.score = 0;
    stats_.scoreText.setString("Score: 0/" + std::to_string(STATS_SCORE_GOAL));

    stats_.finalCooldown.Reset();

    float totalTime = stats_.finalCooldown.GetDuration();
    stats_.finalCooldownText.setString("Time Left (s): " +
                                      std::to_string(static_cast<int>(totalTime)));

    stats_.bestTime = ctx.save.Get<float>(STATS_BEST_TIME_KEY, totalTime);
    stats_.bestTimeText.setString(std::format("Best Time: {:.2f}", stats_.bestTime));
}

void Game::Update()
{
    if (ctx.input.Pressed(Click) && IsTargetHovered())
    {
        EventTargetClicked();
    }

    if (stats_.finalCooldown.IsRunning())
    {
        UpdateTarget();
        UpdateStats();
    }
}

void Clicker::Game::UpdateStats()
{
    float timeLeft = stats_.finalCooldown.GetDuration() - stats_.finalCooldown.GetElapsedTime();
    stats_.finalCooldownText.setString(std::format("Time Left (s): {:.1f}", timeLeft));

    if (stats_.finalCooldown.IsOver())
    {
        LOG_INFO("Time's up! Score: {}", stats_.score);
        ctx.scenes.RestartCurrentScene();
    }
}

void Game::UpdateTarget()
{
    if (target_.teleportCooldown.IsOver())
    {
        EventTargetTeleport();
        target_.teleportCooldown.Restart();
    }

    UpdateTargetColor();
}

void Game::UpdateTargetColor()
{
    float progress =
        target_.teleportCooldown.GetElapsedTime() / target_.teleportCooldown.GetDuration();

    sf::Color color = target_.shape.getFillColor();
    color.a = std::uint8_t(255 * (1 - std::min(progress, 1.f)));

    target_.shape.setFillColor(color);
}
void Clicker::Game::EventTargetClicked()
{
    EventTargetTeleport();
    target_.teleportCooldown.Restart();
    if (stats_.score == 0)
    {
        stats_.finalCooldown.Start();
    }
    EventStatsScoreIncrease();
}
void Clicker::Game::EventTargetTeleport()
{
    sf::Vector2f halfSize = target_.shape.getGlobalBounds().size / 2.f;
    target_.shape.setPosition(ctx.random.Position(halfSize, gConfig.windowSize - halfSize));
}
void Clicker::Game::EventStatsScoreIncrease()
{
    stats_.score++;
    stats_.scoreText.setString(std::format("Score: {}/{}", stats_.score, STATS_SCORE_GOAL));
    if (stats_.score == STATS_SCORE_GOAL)
    {
        float elapsedTime = stats_.finalCooldown.GetElapsedTime();
        ctx.save.Set(STATS_BEST_TIME_KEY, std::min(elapsedTime, stats_.bestTime));
        LOG_INFO("You win! Time: {} seconds", elapsedTime);

        ctx.scenes.RestartCurrentScene();
    }
}

bool Game::IsTargetHovered() const
{
    return Contains(target_.shape, ctx.cursor.GetPosition());
}

void Game::Render() const
{
    ctx.renderer.Draw(target_.shape);

    ctx.renderer.Draw(stats_.scoreText);
    ctx.renderer.Draw(stats_.finalCooldownText);
    ctx.renderer.Draw(stats_.bestTimeText);
}

void Game::OnPause(bool paused)
{
    if (paused)
    {
        target_.teleportCooldown.Stop();
        stats_.finalCooldown.Stop();
    }
    else
    {
        target_.teleportCooldown.Start();
        stats_.finalCooldown.Start();
    }
}