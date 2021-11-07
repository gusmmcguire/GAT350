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

	// samplers
	std::shared_ptr<TextureSampler> texture1 = std::make_unique<TextureSampler>(std::make_unique<Image>("../resources/wood.bmp"));
	std::shared_ptr<TextureSampler> texture2 = std::make_unique<TextureSampler>(std::make_unique<Image>("../resources/metal.bmp"));

	std::shared_ptr<CheckerSampler> black_checker = std::make_unique<CheckerSampler>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 1, 1 });
	std::shared_ptr<CheckerSampler> red_checker = std::make_unique<CheckerSampler>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 0, 0 });

	// scene
	std::unique_ptr<Scene> scene = std::make_unique<Scene>();

	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 0, 4, -10 }, 3.0f, std::make_shared<Lambertian>(texture1))));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 5, 0, -8 }, 2.0f, std::make_shared<Lambertian>(glm::vec3{ 0.2f, 0.2f, 0.8f }))));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ -3, 4, -6 }, 1.5f, std::make_shared<Metal>(texture2, 0.05f))));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 0, 1, -4 }, 1.5f, std::make_shared<Dielectric>(glm::vec3{ 0.5f, 1, 0.5f }, 2.42f))));
	scene->Add(std::move(std::make_unique<Plane>(glm::vec3{ 0, -2, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(black_checker))));
	scene->Add(std::move(std::make_unique<Sphere>(glm::vec3{ 0, 20, 0 }, 10.0f, std::make_shared<Emissive>(glm::vec3{ 0, 10, 0 }))));

	// camera
	glm::vec3 eye = glm::vec3{ 5, 10, 2 };
	glm::vec3 lookAt = glm::vec3{ 0, 0, -10 };
	float focalLength = glm::length(eye - lookAt);
	std::unique_ptr<Camera> camera = std::make_unique<Camera>(eye, lookAt, glm::vec3{ 0, 1, 0 }, 90.0f, glm::ivec2{ framebuffer->colorBuffer.width, framebuffer->colorBuffer.height }, 0.0f, focalLength);

	
	
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