#include "Renderer.h"
#include "Framebuffer.h"
#include <iostream>

Renderer::~Renderer() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

bool Renderer::Initialize(int width, int height, bool fullscreen) {
	this->width = width;
	this->height = height;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow("Ray Tracer", 100, 100, width, height, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Renderer::CopyBuffer(Framebuffer* buffer) {
	SDL_RenderCopy(renderer, buffer->texture, nullptr, nullptr);

}

void Renderer::Present() {
	SDL_RenderPresent(renderer);
}
