#include "Games/IGame.h"


SDL_Manager::SDL_Manager(SDL_Rect props) :
	_window_props(props)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		throw SDL_GetError();
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		throw IMG_GetError();
	}
}

SDL_Manager::~SDL_Manager()
{
	destroy_window();

	SDL_Quit();
}

void SDL_Manager::create_window() 
{
	_window = SDL_CreateWindow("Chess", _window_props.x, _window_props.y, _window_props.w, _window_props.h, 0);

	if (_window == nullptr) {
		throw SDL_GetError();
	}

	_renderer = SDL_CreateRenderer(_window, -1, 0);

	if (_renderer == nullptr)
	{
		throw SDL_GetError();
	}

	SDL_RenderSetLogicalSize(_renderer, _window_props.w, _window_props.h);

	SDL_SetRenderDrawColor(_renderer, 255, 229, 237, 0);
}

void SDL_Manager::destroy_window() 
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
}

void SDL_Manager::render_board(BoardField* fields[][8])
{
	SDL_RenderClear(_renderer);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			RGBA color = fields[i][j]->current_color();
			SDL_SetRenderDrawColor(_renderer, color.red, color.green, color.blue, color.alpha);
			SDL_RenderFillRect(_renderer, &fields[i][j]->rect());

			if (fields[i][j]->piece() != nullptr) {
				const char* filename = fields[i][j]->piece()->filename();

				SDL_RenderCopy(_renderer, load_texture(filename), NULL, &fields[i][j]->rect());
			}
		}
	}

	SDL_RenderPresent(_renderer);
}

SDL_Texture* SDL_Manager::load_texture(const std::string &filename)
{
	SDL_Texture* texture = IMG_LoadTexture(_renderer, filename.c_str());
	if (texture == nullptr) {
		throw SDL_GetError();
	}

	return texture;
}
