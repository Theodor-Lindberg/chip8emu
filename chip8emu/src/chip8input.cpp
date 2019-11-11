#include "chip8input.hpp"

Chip8Input::Chip8Input(Chip8& cpu) : chip8(cpu) { }

void Chip8Input::handle_events(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_X:	chip8.update_key(0x0, event.type == SDL_KEYDOWN);	break;
		case SDL_SCANCODE_1:	chip8.update_key(0x1, event.type == SDL_KEYDOWN);	break;
		case SDL_SCANCODE_2:	chip8.update_key(0x2, event.type == SDL_KEYDOWN);	break;
		case SDL_SCANCODE_3:	chip8.update_key(0x3, event.type == SDL_KEYDOWN);	break;
		case SDL_SCANCODE_Q:	chip8.update_key(0x4, event.type == SDL_KEYDOWN);	break;
		case SDL_SCANCODE_W:	chip8.update_key(0x5, event.type == SDL_KEYDOWN);	break;
		case SDL_SCANCODE_E:	chip8.update_key(0x6, event.type == SDL_KEYDOWN);	break;
		case SDL_SCANCODE_A:	chip8.update_key(0x7, event.type == SDL_KEYDOWN);	break;
		case SDL_SCANCODE_S:	chip8.update_key(0x8, event.type == SDL_KEYDOWN);	break;
		case SDL_SCANCODE_D:	chip8.update_key(0x9, event.type == SDL_KEYDOWN);	break;
		case SDL_SCANCODE_Z:	chip8.update_key(0xA, event.type == SDL_KEYDOWN);	break;
		case SDL_SCANCODE_C:	chip8.update_key(0xB, event.type == SDL_KEYDOWN);	break;
		case SDL_SCANCODE_4:	chip8.update_key(0xC, event.type == SDL_KEYDOWN);	break;
		case SDL_SCANCODE_R:	chip8.update_key(0xD, event.type == SDL_KEYDOWN);	break;
		case SDL_SCANCODE_F:	chip8.update_key(0xE, event.type == SDL_KEYDOWN);	break;
		case SDL_SCANCODE_V:	chip8.update_key(0xF, event.type == SDL_KEYDOWN);	break;
		default: break;
		}
	}
}