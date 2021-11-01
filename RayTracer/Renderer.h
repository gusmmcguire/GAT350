#pragma once
#include "Types.h"
#include "SDL.h"
#include <memory>

class Renderer {
public:
	~Renderer();

	bool Initialize(int width, int height, bool fullscreen = false);
	void CopyBuffer(class Framebuffer* buffer);
	void Present();

public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width = 0;
	int height = 0;
};
