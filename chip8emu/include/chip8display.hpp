#ifndef CHIP8DISPLAY
#define CHIP8DISPLAY

#include "chip8.hpp"
#include "window.hpp"

class Chip8Display : public Window {
public:
	Chip8Display(Window& window, const Chip8& cpu);
	Chip8Display(Window& window, const Chip8& cpu, const SDL_Point& position);
	~Chip8Display() = default;

	/// <summary> Render the graphics buffer to the screen. </summary>
	void render() const;

	SDL_Color background = { background.r = 30, background.g = 120, background.b = 150, background.a = 255 };
	SDL_Color accent = { accent.r = 255, accent.g = 255, accent.b = 255, accent.a = 255 };
	SDL_Point position = { position.x = 0, position.y = 0 };
	uint8_t pixel_size = 10;

private:
	const Chip8& chip8;

	void SetRenderDrawColor(SDL_Renderer* renderer, const SDL_Color& color) const;
};

#endif // !CHIP8DISPLAY