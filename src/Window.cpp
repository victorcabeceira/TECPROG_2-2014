#include "Window.h"
#include "Logger.h"
#include "Configuration.h"

#include <iostream>

SDL_Renderer* Window::sdlRenderer = nullptr;

/**
* The constructor.
* Sets all attributes, and calls the initialize method.
* @param width_ : The desired window width.
* @param height_ : The desired window height.
* @param title_ : The desired window title.
* @note If omitted, window title will be "SDL Window".
* @see Window::initialize
*/
Window::Window(const unsigned int width_, const unsigned int height_, const std::string& title_) :
	
	windowTitle(title_),
	sdlWindow(nullptr)

{
	create(width_, height_);
}
	/**
	* The destructor.
	* Uses the destroy method to delete window.
	* @see Window::destroy
	*/

Window::~Window(){

	destroy();

}

	/**
	* Frees allocated members.
	* Frees the SDL_Renderer and the SDL_Window.
	*/

void Window::destroy(){

	// Destroys the Window renderer.
	SDL_DestroyRenderer(Window::sdlRenderer);
	Window::sdlRenderer = nullptr;

	// Destroys the Window window.
	SDL_DestroyWindow(this->sdlWindow);
	this->sdlWindow = nullptr;

}

	/**
	* Minimizes window.
	* Uses SDLs internal method to minimize the window.
	*/

void Window::minimize(){

	SDL_MinimizeWindow(this->sdlWindow);

}

	/**
	* Maximizes window.
	* Uses SDLs internal method to maximize the window.
	*/

void Window::maximize(){

	SDL_MaximizeWindow(this->sdlWindow);

}

// Draw a white rect filling the whole screen, used for clean.
void Window::clear(){

	SDL_SetRenderDrawColor(Window::sdlRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(Window::sdlRenderer);

}

	/**
	* Renders to screen.
	* Updates the screen with every change in the renderer.
	*/

void Window::render(){

	SDL_RenderPresent(Window::sdlRenderer);

}

	/**
	* Creates the Window, with specified width and height.
	* Can be used either as the creator, or as the resizer.
	*/

void Window::create(const unsigned int width_, const unsigned int height_){
	/// @todo Toggle VSync.

	const Uint32 windowFlags = SDL_WINDOW_SHOWN;
	this->sdlWindow = SDL_CreateWindow(
		this->windowTitle.c_str(), 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width_, height_,
		windowFlags
	);
	
	if(this->sdlWindow != nullptr){

		// Creates the SDL renderer.
		Window::sdlRenderer = SDL_CreateRenderer(this->sdlWindow, -1, SDL_RENDERER_ACCELERATED);
		if(Window::sdlRenderer != nullptr){

			// Set texture filtering to linear.
			SDL_bool linearFilter = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
			
			if(linearFilter){

				Log(INFO) << "Linear texture filtering enabled!";
				rescale(Configuration::getLogicalRenderSize());

			}
			else{
	
				Log(WARN) << "Linear texture filtering disabled!";
	
			}

			Log(DEBUG) << "Game successfully loaded.";
				
		}
		else{
	
			Log(ERROR) << "Renderer could not be created. " << SDL_GetError();
	
		}
	}
	else{
	
		Log(ERROR) << "Window failed to be created. " << SDL_GetError();
	}
}

	/**
	* Resizes the window.
	* @todo Instead of directly choosing width and height, choose from a pre-defined list
	* 	of resolutions.
	*/
		
void Window::resize(const unsigned int width_, const unsigned int height_){

	SDL_SetWindowSize(this->sdlWindow, width_, height_);

}

	/**
	* Rescales the renderization.
	* Set a device independent resolution for rendering.
	* @param size_ : Multiplies Configuration::resolutionWidth and
	* 	Configuration::resolutionHeight for the new resolution.
	* @note Practically, it looks like the camera has a larger field of view, the bigger
	* 	the size_ parameter is.
	* @see SDL_RenderSetLogicalSize
	*/

void Window::rescale(unsigned int size_){
	// Just a precaution, so there is no abuse on the size.
	if(size_ > 10){

		size_ = 10;
		Log(WARN) << "Trying to rescale for a value too big.";

	}

	SDL_RenderSetLogicalSize(
		Window::sdlRenderer,
		Configuration::getResolutionWidth() * size_,
		Configuration::getResolutionHeight() * size_
	);
}

SDL_Renderer* Window::getRenderer(){

	return Window::sdlRenderer;

}

void Window::getLogicalSize(int* w, int* h){

	SDL_RenderGetLogicalSize(Window::getRenderer(), w, h);

}
