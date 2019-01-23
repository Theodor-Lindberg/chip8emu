#ifndef WINDOW
#define WINDOW

#include "SDL.h"
#include <string>

class Window {
public:
	Window(const std::string& title, int width, int height);
	~Window();

	bool is_closed() const;
	void poll_events(SDL_Event& event);
	void clear() const;

protected:
	SDL_Renderer * _renderer = nullptr;

private:
	std::string _title;
	int _width = 800;
	int _height = 600;

	bool _closed;

	bool init();

	SDL_Window * _window = nullptr;
};


#endif !WINDOW