#include "text.h"
#include <iostream>
#include <cassert>
#include "utils.h"

TTF_Font* Text::font_;
int Text::size_;
Texture Text::alphabet_[200];

static void printTTFError(const std::string& msg)
{
        std::cout << msg << ": " << TTF_GetError() << std::endl;
}

void Text::loadContent(Graphics& graphics)
{
        if (!TTF_WasInit() && TTF_Init() == -1) {
                printTTFError("TTF_Init");
                return;
        }
        size_ = 50;
        font_ = TTF_OpenFont("font.ttf", size_);
        if (!font_) {
                printTTFError("TTF_OpenFont");
                return;
        }
        const std::string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "abcdefghijklmnopqrstuvwxyz"
                                "! _-0123456789";
        auto color = SDL_Color{255, 255, 255, 255};
        char buf[2] = {0};
        for (auto& c : str) {
                buf[0] = c;
                auto text_surface = TTF_RenderText_Blended(font_, buf, color);
                if (!text_surface) {
                        printTTFError("TTF_RenderText_Blended");
                        return;
                }
                assert((int)c < 200);
                alphabet_[(int)c] = graphics.loadImage(text_surface);
        }
}

void Text::drawString(Graphics& graphics, const std::string& str, int x, int y,
                      Color* color)
{
        for (auto& c : str)
                drawChar(graphics, c, x += alphabet_[(int)'A'].w, y, color);
}

void Text::drawChar(Graphics& graphics, char c, int x, int y, Color* color)
{
        auto& t = alphabet_[(int)c];
        Graphics::BlitOptions options;
        if (color)
                options.color = *color;
        // TRACE(options.color.r);
        // TRACE(options.color.g);
        // TRACE(options.color.b);
        // TRACE(options.color.a);
        graphics.blit(t, 0, 0, x, y, options);
        x += t.w;
}
