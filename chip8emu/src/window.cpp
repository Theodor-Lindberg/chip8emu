#include "window.hpp"
#include <iostream>

Window::Window(const char* title, int width, int height) {
	_closed = !init(title, width, height);
}

Window::~Window() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

bool Window::is_closed() const {
	return _closed;
}

void Window::handle_event(SDL_Event &event) {
	switch (event.type) {
	case SDL_QUIT:
		_closed = true;
		break;
	default:
		break;
	}
}

void Window::clear() const {
	SDL_RenderPresent(_renderer);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);
}

bool Window::init(const char* title, int width, int height) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		std::cerr << "Could not initialize SDL video and video." << std::endl;
		return false;
	}

	_window = SDL_CreateWindow(title,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_RESIZABLE);

	if (_window == nullptr) {
		std::cerr << "Failed to create window." << std::endl;
		return false;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (_renderer == nullptr) {
		std::cerr << "Failed to create renderer." << std::endl;
		return false;
	}

	return true;
}