#pragma once

#include <array>
#include <map>
#include <memory>
#include <string>

#include <SDL.h>
#include <GL/glew.h>

struct Texture
{
        GLuint id;
        int w, h;
};

struct Color
{
        float r, g, b, a;
};

class Graphics
{
  public:
        struct BlitOptions
        {
                int sprite_w{-1};
                int sprite_h{-1};
                Color color{1, 1, 1, 1};  // tint color
                float scale_w{1};         // width scale
                float scale_h{1};         // height scale
                float rotation{0};        // rotation in radians
        };

        Graphics(SDL_Window *win);
        Texture loadImage(const std::string &file);
        Texture loadImage(SDL_Surface *surface);
        void blit(const Texture &texture, int src_x, int src_y, int x, int y);
        void blit(const Texture &texture, int src_x, int src_y, int x, int y,
                  const BlitOptions &options);
        void clear()
        {
                glClear(GL_COLOR_BUFFER_BIT);
        }
        void flip()
        {
                SDL_GL_SwapWindow(window);
        }

        static constexpr int SCREEN_WIDTH = 480;
        static constexpr int SCREEN_HEIGHT = 600;

        static float units_x(float pixels)
        {
                return pixels / SCREEN_WIDTH * 2;
        }
        static float units_y(float pixels)
        {
                return pixels / SCREEN_HEIGHT * -2;
        }

  private:
        std::map<std::string, Texture> texture_map;
        SDL_Window *window;
};
