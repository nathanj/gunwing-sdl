#include "hud.h"

#include "game-state.h"
#include "font-medal.h"

void Hud::draw(Graphics& graphics)
{
        FontMedal::draw(graphics, GameState::ship->medal_count(), {60, 32});
}
