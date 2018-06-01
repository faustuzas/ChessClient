#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "BoardField/BoardField.h"

class SDL_Manager
{
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Rect _window_props;

	SDL_Texture* load_texture(const std::string &filename);
public:
	SDL_Manager(SDL_Rect props);
	~SDL_Manager();

	void create_window();
	void destroy_window();
	void render_board(BoardField* current_arrangement[][8]);
	int window_height() const { return _window_props.h; }
	int window_width() const { return _window_props.w; }
};
