#ifndef WINDOW
#define WINDOW

#include "SDL.h"
#include <string>

class Window {
public:
	Window(const char* title, int width, int height);
	~Window();

	/// <summary> Return true if the window is open, otherwise false. </summary>
	[[nodiscard]] bool is_open() const;

	/// <summary> Handle event. </summary>
	/// <param name="event"> The event to handle. </param>
	void handle_event(SDL_Event& event);

	/// <summary> Clear the screen. </summary>
	void clear() const;

	/// <summary> Get the width of the screen. </summary>
	[[nodiscard]] int get_width() const;

	/// <summary> Get the height of the screen. </summary>
	[[nodiscard]] int get_height() const;

protected:
	SDL_Renderer* renderer = nullptr;

private:
	bool window_open;
	int width, height;
	SDL_Window* window = nullptr;

	/// <summary> Initialize the gui. </summary>
	/// <param name="title"> The title of the window. </param>
	/// <param name="width"> The width of the window. </param>
	/// <param name="height"> The height of the window. </param>
	bool init(const char* title, int width, int height);
};


#endif !WINDOW