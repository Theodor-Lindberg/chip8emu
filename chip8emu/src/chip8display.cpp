#include "chip8display.hpp"

Chip8Display::Chip8Display(Window& window, const Chip8& cpu) :
	Window(window), chip8(cpu) { }

Chip8Display::Chip8Display(Window& window, const Chip8& cpu, const SDL_Point& position) :
	Window(window), chip8(cpu) {
	this->position = SDL_Point(position);
}

void Chip8Display::render() const {
	const bool* const gfx_buffer = chip8.get_gfx_buffer();

	for (int i = 0; i < chip8.SCREEN_WIDTH * chip8.SCREEN_HEIGHT; i++) {
		SetRenderDrawColor(renderer, gfx_buffer[i] ? accent : background);
		SDL_Rect pixel = { (i % (int)chip8.SCREEN_WIDTH) * pixel_size + position.x, (i / (int)chip8.SCREEN_WIDTH) * pixel_size + position.y,
			pixel_size, pixel_size };
		SDL_RenderFillRect(renderer, &pixel);
	}
}

void Chip8Display::SetRenderDrawColor(SDL_Renderer* renderer, const SDL_Color& color) const {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}