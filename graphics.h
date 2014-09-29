#pragma once

#include <array>
#include <map>
#include <memory>
#include <string>

#include <SDL.h>
#include <GL/glew.h>

struct Texture {
	GLuint id;
	int w, h;
};

struct Color {
        float r, g, b, a;
};

class Graphics {
public:
	enum class BlitFlags {
		NONE            = 1 << 0,
		HORIZONTAL_FLIP = 1 << 1,
		VERTICAL_FLIP   = 1 << 2,
	};

	Graphics(SDL_Window* win);
	Texture loadImage(const std::string& file);
	void blit(const Texture& texture, int src_x, int src_y, int x, int y,
                  int sprite_w = -1, int sprite_h = -1,
                  BlitFlags flags = BlitFlags::NONE,
                  const Color* color = NULL);
	void clear() { glClear(GL_COLOR_BUFFER_BIT) ; }
	void flip() { SDL_GL_SwapWindow(window); }

	static constexpr int SCREEN_WIDTH = 480;
	static constexpr int SCREEN_HEIGHT = 680;

	static float units_x(float pixels) { return pixels / SCREEN_WIDTH * 2; }
	static float units_y(float pixels) { return pixels / SCREEN_HEIGHT * -2; }

private:
	std::map<std::string, Texture> texture_map;
	SDL_Window* window;
};

inline Graphics::BlitFlags operator|(Graphics::BlitFlags a, Graphics::BlitFlags b)
{
	return static_cast<Graphics::BlitFlags>(static_cast<int>(a) |
						static_cast<int>(b));
}
inline Graphics::BlitFlags operator&(Graphics::BlitFlags a, Graphics::BlitFlags b)
{
	return static_cast<Graphics::BlitFlags>(static_cast<int>(a) &
						static_cast<int>(b));
}
