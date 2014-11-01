#include "graphics.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <cassert>

#include <SDL_image.h>

static void printSDLError(const std::string &msg)
{
        std::cout << msg << ": " << SDL_GetError() << std::endl;
}

Graphics::Graphics(SDL_Window *win) : window(win)
{
        SDL_GL_CreateContext(win);

        glClearColor(0, 0, 0, 0);
        glEnable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}

Texture Graphics::loadImage(const std::string &file)
{
        // Load up the cached texture if possible.
        auto p = texture_map.find(file);
        if (p != texture_map.end())
                return p->second;

        // Otherwise load the image and store it in the map.
        auto surface = std::unique_ptr<SDL_Surface, void (*)(SDL_Surface *)>(
            IMG_Load(file.c_str()), &SDL_FreeSurface);
        if (surface == NULL) {
                printSDLError("IMG_Load " + file);
                abort();
        }

        auto t = loadImage(surface.get());
        texture_map[file] = t;
        return t;
}

Texture Graphics::loadImage(SDL_Surface *surface)
{
        GLuint id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, surface->format->BytesPerPixel,
                     surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     surface->pixels);

        Texture t{id, surface->w, surface->h};

        return t;
}

void Graphics::blit(const Texture &texture, int src_x, int src_y, int x, int y)
{
        BlitOptions options;
        blit(texture, src_x, src_y, x, y, options);
}

void Graphics::blit(const Texture &texture, int src_x, int src_y, int x, int y,
                    const BlitOptions &options)
{
        assert(texture.w > 0);

        const auto sprite_w = options.sprite_w == -1 ? texture.w : options.sprite_w;
        const auto sprite_h = options.sprite_h == -1 ? texture.h : options.sprite_h;
        const auto scale_w = options.scale_w;
        const auto scale_h = options.scale_h;
        const auto& color = options.color;

        const float sx = src_x * 1.0f / texture.w;
        const float tx = (src_x + sprite_w) * 1.0f / texture.w;
        const float sy = src_y * 1.0f / texture.h;
        const float ty = (src_y + sprite_h) * 1.0f / texture.h;

        glBindTexture(GL_TEXTURE_2D, texture.id);

        glPushMatrix();

        glTranslatef(x + sprite_w / 2, y + sprite_h / 2, 0.0f);
        glRotatef(options.rotation, 0, 0, 1);
        glTranslatef(-(x + sprite_w / 2), -(y + sprite_h / 2), 0.0f);

        glColor4f(color.r, color.g, color.b, color.a);

        glBegin(GL_QUADS);
        // Top-left vertex (corner)
        glTexCoord2f(sx, sy);
        glVertex3f(x, y, 0);

        // Top right
        glTexCoord2f(tx, sy);
        glVertex3f(x + sprite_w * scale_w, y, 0);

        // Bottom-right vertex (corner)
        glTexCoord2f(tx, ty);
        glVertex3f(x + sprite_w * scale_w, y + sprite_h * scale_h, 0);

        // Bottom left
        glTexCoord2f(sx, ty);
        glVertex3f(x, y + sprite_h * scale_h, 0);
        glEnd();

        glPopMatrix();
}
