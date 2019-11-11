#ifndef CHIP8INPUT
#define CHIP8INPUT

#include "chip8.hpp"
#include "SDL.h"

class Chip8Input {
public:
	Chip8Input(Chip8& cpu);

	/// <summary> Handle event. </summary>
	/// <param name="event"> The event to handle. </param>
	void handle_events(const SDL_Event& event);

private:
	Chip8& chip8;
};

#endif // !CHIP8INPUT