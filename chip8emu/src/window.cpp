#include "window.hpp"
#include <iostream>

Window::Window(const char* title, int width, int height) {
	window_open = init(title, width, height);
}

Window::~Window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Window::is_open() const {
	return window_open;
}

void Window::handle_event(SDL_Event &event) {
	switch (event.type) {
	case SDL_QUIT:
		window_open = false;
		break;
	default:
		break;
	}
}

void Window::clear() const {
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

int Window::get_width() const {
	return width;
}

int Window::get_height() const {
	return height;
}

bool Window::init(const char* title, int width, int height) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		std::cerr << "Could not initialize SDL video and video." << std::endl;
		return false;
	}

	window = SDL_CreateWindow(title,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_RESIZABLE);

	if (window == nullptr) {
		std::cerr << "Failed to create window." << std::endl;
		return false;
	}

	this->width = width;
	this->height = height;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cerr << "Failed to create renderer." << std::endl;
		return false;
	}

	return true;
}