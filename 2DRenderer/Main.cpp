#include "Renderer.h"
#include "Framebuffer.h"
#include "Image.h"

#include <iostream>
#include <SDL.h>

int main(int, char**) {
	const int WIDTH = 1280;
	const int HEIGHT = 720;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);

	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer->width, renderer->height);

	bool quit = false;
	SDL_Event event;
	while (!quit) {
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}

		framebuffer->Clear({ 0,0,0,0 });

		for (int i = 0; i < 100; i++) {
			framebuffer->DrawPoint(rand() % renderer->width, rand() % renderer->height, { 0, 255, 0, 0 });
		}
		for (int i = 0; i < 20; i++) {
			framebuffer->DrawRect(rand() % renderer->width, rand() % renderer->height, 20, 20, { 0, 0, 255, 0 });
		}
		for (int i = 0; i < 20; i++) {
			framebuffer->DrawLine(renderer->width >> 1, renderer->height >> 1, rand() % renderer->width, rand() % renderer->height, { 255, 255, 255, 0 });
		}

		for (int i = 0; i < 10; i++) {
			framebuffer->DrawQuadraticCurve(
				rand() % renderer->width, rand() % renderer->height,
				rand() % renderer->width, rand() % renderer->height,
				rand() % renderer->width, rand() % renderer->height, 30, { 255, 255, 0, 255 });
		}
		for (int i = 0; i < 10; i++) {
			framebuffer->DrawCubicCurve(
				rand() % renderer->width, rand() % renderer->height,
				rand() % renderer->width, rand() % renderer->height,
				rand() % renderer->width, rand() % renderer->height,
				rand() % renderer->width, rand() % renderer->height,
				30, { 0, 255, 255, 255 });
		}

		std::unique_ptr<Image> image = std::make_unique<Image>();
		image->Load("../resources/color.bmp");
		image->Flip();
		framebuffer->DrawImage(30,30,image.get());
		

		framebuffer->Update();
		renderer->CopyBuffer(framebuffer.get());
		renderer->Present();
	}

	SDL_Quit();

	return 0;
}
