#include "Text.h"
#include "Logger.h"
 
Text::Text(const double x_, const double y_, const char* path_, const int size_,
	const char* text_, const SDL_Color color_) :
	Entity(x_, y_),
	font(nullptr)
{
	this->font = TTF_OpenFont(path_, size_);

	if(this->font == nullptr){
		Log(ERROR) << "Failed to open font." << TTF_GetError();
	}

	SDL_Surface* surface = TTF_RenderText_Blended(this->font, text_, color_);
	const int surfaceW = surface->w;
	const int surfaceH = surface->h;

	if(surface != nullptr){
		this->sprite = new Sprite(surface);

		// Idk.
		this->sprite->setWidth(surfaceW);
		this->sprite->setHeight(surfaceH);
	}
	else{
		Log(ERROR) << "Could not load font surface.";
	}
	
}

Text::Text(const double x_, const double y_, const char* path_, const int size_,
	const char* text_) :
	Entity(x_, y_),
	font(nullptr)
{
	this->font = TTF_OpenFont(path_, size_);

	if(this->font == nullptr){
		Log(ERROR) << "Failed to open font." << TTF_GetError();
	}

	SDL_Surface* surface = TTF_RenderText_Blended(this->font, text_, {0xCE, 0xCE, 0xCE, 255});
	const int surfaceW = surface->w;
	const int surfaceH = surface->h;

	if(surface != nullptr){
		this->sprite = new Sprite(surface);

		// Idk.
		this->sprite->setWidth(surfaceW);
		this->sprite->setHeight(surfaceH);
	}
	else{
		Log(ERROR) << "Could not load font surface.";
	}
	
}

Text::~Text(){
	if(this->sprite != nullptr){
		delete this->sprite;
		this->sprite = nullptr;
	}

	TTF_CloseFont(this->font);
}

void Text::changeText(const char* text_, const SDL_Color color_){

	if(this->sprite != nullptr){
		delete this->sprite;
		this->sprite = nullptr;
	}

	SDL_Surface* surface = TTF_RenderText_Blended(this->font, text_, color_);
	const int surfaceW = surface->w;
	const int surfaceH = surface->h;

	if(surface != nullptr){
		this->sprite = new Sprite(surface);

		// Idk.
		this->sprite->setWidth(surfaceW);
		this->sprite->setHeight(surfaceH);
	}
	else{
		Log(ERROR) << "Could not load font surface.";
	}

}

void Text::changeText(const char* text_){

	if(this->sprite != nullptr){
		delete this->sprite;
		this->sprite = nullptr;
	}

	SDL_Surface* surface = TTF_RenderText_Blended(this->font, text_, {0xCE, 0xCE, 0xCE, 255});
	const int surfaceW = surface->w;
	const int surfaceH = surface->h;

	if(surface != nullptr){
		this->sprite = new Sprite(surface);

		// Idk.
		this->sprite->setWidth(surfaceW);
		this->sprite->setHeight(surfaceH);
	}
	else{
		Log(ERROR) << "Could not load font surface.";
	}

}

void Text::update(const double dt_){
	(void(dt_)); //unused
}

void Text::render(const double cameraX_, const double cameraY_){
	const int dx = this->x - cameraX_;
	const int dy = this->y - cameraY_;

	if(this->sprite != nullptr){
		this->sprite->render(dx, dy);
	}
	else{
		Log(WARN) << "Null sprite for text";
	}
}
