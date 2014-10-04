#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <memory>

#include <SDL.h>
#include <GL/glew.h>

#include "background.h"
#include "bomb.h"
#include "boss2.h"
#include "boss.h"
#include "electric-ball.h"
#include "electric-beam.h"
#include "enemy.h"
#include "font-medal.h"
#include "font-score.h"
#include "font-small.h"
#include "fps.h"
#include "game-state.h"
#include "graphics.h"
#include "healthbar.h"
#include "hud.h"
#include "input.h"
#include "reflective-beam.h"
#include "ship.h"
#include "shrapnel-bomb.h"
#include "shrapnel-enemy.h"
#include "shrapnel.h"
#include "stage1.h"
#include "stage2.h"
#include "stage-cleared.h"
#include "utils.h"
#include "warning.h"

static bool quit = false;

static void printSDLError(const std::string &msg)
{
        std::cout << msg << ": " << SDL_GetError() << std::endl;
}

static void handleEvents(Input &input)
{
        SDL_Event e;

        while (SDL_PollEvent(&e)) {
                switch (e.type) {
                        case SDL_QUIT:
                                quit = true;
                                break;
                        default:
                                input.handleEvent(e);
                                break;
                }
        }
        input.handleJoystick(0);
}

int main()
{
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
                printSDLError("SDL_Init");
                return 1;
        }
        atexit(SDL_Quit);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        auto win = std::unique_ptr<SDL_Window, void (*)(SDL_Window *)>(
            SDL_CreateWindow("Gunwing SDL", 100, 100, Graphics::SCREEN_WIDTH,
                             Graphics::SCREEN_HEIGHT,
                             SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL),
            &SDL_DestroyWindow);

        if (win == nullptr) {
                printSDLError("SDL_CreateWindow");
                return 1;
        }

        Graphics graphics(win.get());
        Background::loadContent(graphics);
        Bomb::loadContent(graphics);
        Boss::loadContent(graphics);
        Bullet::loadContent(graphics);
        Enemy::loadContent(graphics);
        EnemyChunk::loadContent(graphics);
        FontMedal::loadContent(graphics);
        FontScore::loadContent(graphics);
        FontSmall::loadContent(graphics);
        HealthBar::loadContent(graphics);
        Hud::loadContent(graphics);
        Medal::loadContent(graphics);
        Ship::loadContent(graphics);
        Shrapnel::loadContent(graphics);
        ShrapnelBomb::loadContent(graphics);
        ShrapnelEnemy::loadContent(graphics);
        Warning::loadContent(graphics);
        StageCleared::loadContent(graphics);
        ElectricBall::loadContent(graphics);
        ElectricBeam::loadContent(graphics);
        ReflectiveBeam::loadContent(graphics);
        Boss2::loadContent(graphics);
        std::shared_ptr<Stage> stage = std::make_shared<Stage2>();

        FramesPerSecond fps;
        Input input;
        Ship ship;
        Hud hud;
        GameState::ship = &ship;
        GameState::hud = &hud;

        if (SDL_NumJoysticks() > 0)
                input.openJoystick(0);

        auto last_tick = SDL_GetTicks();
        while (!quit) {
                input.beginNewFrame();

                handleEvents(input);

                if (input.wasKeyPressed(SDLK_ESCAPE))
                        quit = true;
                ship.handleInput(input);

                auto tick = SDL_GetTicks();
                std::chrono::milliseconds delta(tick - last_tick);
                last_tick = tick;

                // Update
                fps.update(delta);
                stage->update(delta);
                GameState::update(delta);

                if (stage->next_stage())
                        stage = std::make_shared<Stage1>();

                // Render the scene
                graphics.clear();
                stage->draw(graphics);
                GameState::draw(graphics);
                graphics.flip();
        }

        std::cout << "FPS: " << fps.fps() << std::endl;

        return 0;
}
