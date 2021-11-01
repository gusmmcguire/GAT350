#include "Renderer.h"
#include "Framebuffer.h"
#include "PostProcess.h"
#include "Image.h"
#include "Tracer.h"
#include "Scene.h"
#include "Camera.h"

#include <iostream>
#include <SDL.h>

int main(int, char**) {
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);

	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer.get()->width, renderer.get()->height);

	// ray tracer
	std::unique_ptr<Tracer> tracer = std::make_unique<Tracer>();

	// scene
	std::unique_ptr<Scene> scene = std::make_unique<Scene>();

	//adding materials
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 0,0,-10 }, 3.0f, std::make_shared<Lambertian>(glm::vec3{ 1,0,0 }))));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 3,3,-8 }, 1.0f, std::make_shared<Metal>(glm::vec3{ 0,1,0 }, 0.0f))));
	scene->Add(std::move(std::make_unique<Plane>(glm::vec3{ 0,-3,0 }, glm::vec3{ 0,1,0 }, std::make_shared<Metal>(glm::vec3{ 0.5f,0.5f,0.5f }, 0.0f))));

	float focalLength = glm::length(glm::vec3{5,5,0}-glm::vec3{0,0,10});
	std::unique_ptr<Camera> camera = std::make_unique<Camera>(glm::vec3{ 5, 5, 5 }, glm::vec3{ 0, 0, -10 }, glm::vec3{ 0, 1, 0 }, 90.0f, glm::ivec2{ framebuffer->colorBuffer.width, framebuffer->colorBuffer.height }, 0.0f, focalLength);
	framebuffer->Clear({ 0,0,0,0 });
	tracer->Trace(framebuffer->colorBuffer, scene.get(), camera.get());
	framebuffer->Update();

	bool quit = false;
	SDL_Event event;
	while (!quit) {
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}


		renderer->CopyBuffer(framebuffer.get());

		renderer->Present();
	}

	SDL_Quit();

	return 0;
}